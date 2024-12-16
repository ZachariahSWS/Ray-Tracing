#pragma once
#include "definitions.hpp"
#include "constants.hpp"
#include <cmath>

struct Material {
    colorF tint = {1.0, 1.0, 1.0};
    fp32 emission = 0.0; // emission assumed to be a scale of a materials tint for cache alignment
    //colorF emission = {0.0, 0.0, 0.0};
    fp32 ior = 1.0;
    fp16 roughness = 0.0; // lower precision for cache alignment
    fp16 metallic = 0.0; // lower precision for cache alignment
    bool isTransparent = false;
};

Material Void;

struct Ray {
    Material surfaceMaterial; // 32 bytes
    position origin = {0.0, 0.0, 0.0}; // 16 bytes
    unitVec direction; // 16 bytes
    unitVec surfaceNormal; // 16 bytes
    // Will be decreased
    colorF tint = {1.0, 1.0, 1.0}; // 16 bytes
    // Will be increased
    colorF color = {0.0, 0.0, 0.0}; // 16 bytes
    // Will be decreased
    fp32 distance = INFINITY_F; // 4 bytes
    fp32 currentIOR = 1.0; // 4 bytes
    ui32 depth = 0; // 4 bytes
    // 128 bytes, the size of a cache line on the apple m2 chip
    void update(){
        depth++;
        if (distance != INFINITY_F) {
            origin += direction * distance;
            distance = INFINITY_F;
        } else {
            surfaceMaterial = Void;
        }
        tint *= surfaceMaterial.tint;
        color += surfaceMaterial.emission * tint; // goes after tint update to include the surface's tint
        // TODO: Reflect and Refract Ray
        currentIOR = surfaceMaterial.ior;
    }
};

class Hittable {
protected:
    Material material;
public:
    Hittable(const Material &mat):material(mat){}
    virtual ~Hittable() = default;
    virtual void intersection(Ray &ray) const = 0;
    virtual void testHit(Ray &ray, const unitVec &normal, const fp32 &t, const Material &mat) const final {
        if (t > 0.0f && t < ray.distance) {
            ray.distance = t;
            ray.surfaceNormal = normal;
            ray.surfaceMaterial = mat;
        }
    }
};

class Sphere: public Hittable {
private:
    position center;
    fp32 radius_squared;
public:
    Sphere(fp32 radius, position center_pos, const Material &mat):
        Hittable(mat),
        radius_squared(radius * radius),
        center(center_pos) {}

    void set_radius(fp32 new_radius) {
        radius_squared = new_radius * new_radius;
    }

    void intersection(Ray &ray) const override {
        // Normally origin - center, other way around so numbers are positive
        position relative_position = center - ray.origin;
        fp32 dot_product = dot(ray.direction, relative_position);
        // Determinant
        fp32 nabla = dot_product * dot_product - simd::length_squared(relative_position) + radius_squared;
        // If no intersection change nothing
        if (nabla < 0) return;

        fp32 root_nabla = std::sqrt(nabla);
        // distance to closer intersection
        fp32 t = dot_product - root_nabla;
        unitVec normal = normalize(simd_muladd(ray.direction, t, ray.origin) - center);
        testHit(ray, normal, t, material);

        //distance to farther intersection
        t = dot_product + root_nabla;
        normal = normalize(simd_muladd(ray.direction, t, ray.origin) - center);
        testHit(ray, normal, t, material);
    }
};

class Triangle : public Hittable {
private:
    position vertex;
    position edge1;
    position edge2;
    unitVec normal;
public:
    Triangle(const position &v1, const position &v2, const position &v3, const Material &mat):
        Hittable(mat),
        vertex(v1),
        edge1(v2 - v1),
        edge2(v3 - v1),
        normal(normalize(cross(edge1, edge2))){}

    void intersection(Ray &ray) const override{
        // Möller-Trumbore ray-triangle intersection algorithm
        fp32 dot_product = dot(normal, ray.direction);
        // Escape if triangle and ray are parallel
        if (dot_product < EPSILON && dot_product > -EPSILON) return;

        position relative_position = ray.origin - vertex;

        fp32 u = dot(cross(-ray.direction, relative_position), edge2);
        if (u > 0.0f || u < dot_product) return;

        fp32 v = dot(cross(relative_position, edge1), ray.direction);
        if (v > 0.0f || u + v < dot_product) return;

        fp32 t = - dot(normal, relative_position) / dot_product;
        testHit(ray, normal, t, material);

    }
};

struct Box {
    // Axis-Aligned Bounding Box
    // Doesn't have a material, it will just be used to implement a BVH
    position coordMin;
    position coordMax;

    Box(const position &corner1, const position &corner2):
        coordMin(corner1),
        coordMax(corner2){}

    [[nodiscard]] bool intersect(const Ray &ray) const {
        position inv_direction = simd::recip(ray.direction);
        position t1 = (coordMin - ray.origin) * inv_direction;
        position t2 = (coordMax - ray.origin) * inv_direction;
        fp32 tExit = simd::reduce_min(simd::max(t1, t2));
        if (tExit < 0) return false; // Check if box is behind camera
        fp32 tEnter = simd::reduce_max(simd::min(t1, t2));
        return (tEnter <= tExit);
    }
};
