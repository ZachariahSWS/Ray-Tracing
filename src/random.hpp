#pragma once
#include "definitions.hpp"
#include "constants.hpp"
#include <type_traits>

// Type traits for detecting vector types
template<typename T>
struct is_uint8_vector : std::false_type {};

template<typename T>
struct is_uint16_vector : std::false_type {};

template<typename T>
struct is_uint32_vector : std::false_type {};

template<typename T>
struct is_uint64_vector : std::false_type {};

// Specializations for 8-bit vectors
template<> struct is_uint8_vector<ui8x1> : std::true_type {};
template<> struct is_uint8_vector<ui8x2> : std::true_type {};
template<> struct is_uint8_vector<ui8x3> : std::true_type {};
template<> struct is_uint8_vector<ui8x4> : std::true_type {};
template<> struct is_uint8_vector<ui8x8> : std::true_type {};
template<> struct is_uint8_vector<ui8x16> : std::true_type {};
template<> struct is_uint8_vector<ui8x32> : std::true_type {};
template<> struct is_uint8_vector<ui8x64> : std::true_type {};

// Specializations for 16-bit vectors
template<> struct is_uint16_vector<ui16x1> : std::true_type {};
template<> struct is_uint16_vector<ui16x2> : std::true_type {};
template<> struct is_uint16_vector<ui16x3> : std::true_type {};
template<> struct is_uint16_vector<ui16x4> : std::true_type {};
template<> struct is_uint16_vector<ui16x8> : std::true_type {};
template<> struct is_uint16_vector<ui16x16> : std::true_type {};
template<> struct is_uint16_vector<ui16x32> : std::true_type {};

// Specializations for 32-bit vectors
template<> struct is_uint32_vector<ui32x1> : std::true_type {};
template<> struct is_uint32_vector<ui32x2> : std::true_type {};
template<> struct is_uint32_vector<ui32x3> : std::true_type {};
template<> struct is_uint32_vector<ui32x4> : std::true_type {};
template<> struct is_uint32_vector<ui32x8> : std::true_type {};
template<> struct is_uint32_vector<ui32x16> : std::true_type {};

// Specializations for 64-bit vectors
template<> struct is_uint64_vector<ui64x1> : std::true_type {};
template<> struct is_uint64_vector<ui64x2> : std::true_type {};
template<> struct is_uint64_vector<ui64x3> : std::true_type {};
template<> struct is_uint64_vector<ui64x4> : std::true_type {};
template<> struct is_uint64_vector<ui64x8> : std::true_type {};

// Primary template declaration (will cause compile error if used with unsupported type)
template<typename UnsignedVector>
inline void pcgHash(UnsignedVector& seeds);

// Specialization for 8-bit vectors
template<typename UnsignedVector>
inline void pcgHash(UnsignedVector& seeds) requires is_uint8_vector<UnsignedVector>::value {
    seeds = (seeds * 141u + 17u) & 0xFFu;
}

// Specialization for 16-bit vectors
template<typename UnsignedVector>
inline void pcgHash(UnsignedVector& seeds) requires is_uint16_vector<UnsignedVector>::value {
    seeds = (seeds * 12829u) + 47989u;
}

// Specialization for 32-bit vectors
template<typename UnsignedVector>
inline void pcgHash(UnsignedVector& seeds) requires is_uint32_vector<UnsignedVector>::value {
    UnsignedVector state = seeds * 747796405u + 2891336453u;
    UnsignedVector word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    seeds = (word >> 22u) ^ word;
}

// Specialization for 64-bit vectors
template<typename UnsignedVector>
inline void pcgHash(UnsignedVector& seeds) requires is_uint64_vector<UnsignedVector>::value {
    UnsignedVector state = seeds * 6364136223846793005ULL + 1442695040888963407ULL;
    UnsignedVector rot = state >> 59u;
    UnsignedVector xsl = ((state >> 18u) ^ state) >> 27u;
    seeds = (xsl >> rot) | (xsl << ((-rot) & 63u));
}

inline position pointInUnitSquare(ui32x2 &seeds){
    pcgHash(seeds);
    fp32x2 xy = simd_muladd(simd_float2(seeds), INV_INT_MAX_F, -1.0f);
    return simd_make_float3(xy);
}

inline position pointInUnitDisk(ui32x2 &seeds){
    fp32x2 p;
    do {
        pcgHash(seeds);
        p = simd_muladd(simd_float2(seeds), INV_INT_MAX_F, -1.0f);
    } while (simd::length_squared(p) > 1);
    return simd_make_float3(p);
}

inline unitVec randomUnitVector(ui32x3 &seeds){
    position vector;
    do {
        pcgHash(seeds);
        vector = simd_muladd(simd_float3(seeds), INV_INT_MAX_F, -1.0f);
    } while (simd::length_squared(vector) > 1);
    return normalize(vector);
}

inline unitVec randomHemispherePoint(const unitVec &normal, ui32x3 &seeds) {
    unitVec inUnitSphere = randomUnitVector(seeds);
    return (dot(inUnitSphere, normal) > 0.0f) ? inUnitSphere : -inUnitSphere;
}

inline unitVec randomCosineDirection(ui32x2 &seeds) {
    pcgHash(seeds);
    fp32x2 r = simd::make_float2(seeds) * INV_UINT_MAX_F;

    fp32 phi = 2.0f * PI * r[0];
    fp32 sqrtR1 = sqrt(r[1]);
    fp32x1 x = cos(phi) * sqrtR1;
    fp32x1 y = sin(phi) * sqrtR1;
    fp32x1 z = sqrt(1.0f - r[1]);

    return simd_make_float3(x, y, z);
}

inline fp32 random01(ui32 &seed) {
    pcgHash(seed);
    return seed * INV_UINT_MAX_F;
}
