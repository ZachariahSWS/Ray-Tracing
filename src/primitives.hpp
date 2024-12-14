#pragma once
#include "definitions.hpp"
#include "constants.hpp"
#include <cmath>

struct Ray {
    position origin = {0.0, 0.0, 0.0}; // 16 bytes
    unitVec direction; // 16 bytes
    unitVec inv_direction; // 16 bytes
    unitVec surfaceNormal; // 16 bytes
    // Will be decreased
    colorF color = {1.0, 1.0, 1.0}; // 16 bytes
    colorF surfaceColor;
    // Will be decreased
    f32 distance = INFINITY_F; // 4 bytes
    f32 currentIOR = 1.0; // 4 bytes
    f32 surfaceIOR; // 4 bytes
    u32 depth = 0; // 4 bytes
    // 112 bytes - m2 chip cache line is 128 bytes
};

struct Material {
    colorF color = {1.0, 1.0, 1.0};
    f32 ior = 1.0;
    f32 roughness = 0.0;
    f32 metallic = 0.0;
    bool isTransparent = false;
};

class Hittable {
protected:
    Material material;
public:
    Hittable(const Material &mat):material(mat){}
    virtual ~Hittable() = default;
    virtual void intersection(Ray &ray) const = 0;
    virtual void updateRay(Ray &ray, const unitVec &normal, const f32 &t) const {
        if (t > 0.0f && t < ray.distance) {
            ray.distance = t;
            ray.surfaceNormal = normal;
            ray.surfaceColor = material.color;
            ray.surfaceIOR = material.ior;
        }
    }
};

class Sphere: public Hittable {
private:
    position center;
    f32 radius_squared;
public:
    Sphere(f32 radius, position center_pos, const Material &mat):
        Hittable(mat),
        radius_squared(radius * radius),
        center(center_pos) {}

    void set_radius(f32 new_radius) {
        radius_squared = new_radius * new_radius;
    }

    void intersection(Ray &ray) const override {
        // Normally origin - center, other way around so numbers are positive
        position relative_position = center - ray.origin;
        f32 dot_product = dot(ray.direction, relative_position);
        // Determinant
        f32 nabla = dot_product * dot_product - simd::length_squared(relative_position) + radius_squared;
        // If no intersection change nothing
        if (nabla < 0) return;

        f32 root_nabla = std::sqrt(nabla);
        // distance to closer intersection
        f32 t = dot_product - root_nabla;
        unitVec normal = normalize(simd_muladd(ray.direction, t, ray.origin) - center);
        updateRay(ray, normal, t);

        //distance to farther intersection
        t = dot_product + root_nabla;
        normal = normalize(simd_muladd(ray.direction, t, ray.origin) - center);
        updateRay(ray, normal, t);
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
        f32 dot_product = dot(normal, ray.direction);
        // Escape if triangle and ray are parallel
        if (dot_product < EPSILON && dot_product > -EPSILON) return;

        position relative_position = ray.origin - vertex;

        f32 u = dot(cross(-ray.direction, relative_position), edge2);
        if (u > 0.0f || u < dot_product) return;

        f32 v = dot(cross(relative_position, edge1), ray.direction);
        if (v > 0.0f || u + v < dot_product) return;

        f32 t = - dot(normal, relative_position) / dot_product;
        updateRay(ray, normal, t);

    }
};

struct Box {
    // Axis-Aligned Bounding Box
    position coordMin;
    position coordMax;

    Box(const position &corner1, const position &corner2):
        coordMin(corner1),
        coordMax(corner2){}

    bool intersect(const Ray &ray) const {
        position t1 = (coordMin - ray.origin) * ray.inv_direction;
        position t2 = (coordMax - ray.origin) * ray.inv_direction;
        f32 tExit = simd::reduce_min(simd::max(t1, t2));
        if (tExit < 0) return false; // Check if box is behind camera
        f32 tEnter = simd::reduce_max(simd::min(t1, t2));
        return (tEnter <= tExit);
    }
};
