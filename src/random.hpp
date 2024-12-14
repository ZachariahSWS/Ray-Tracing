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
template<> struct is_uint8_vector<u8x1> : std::true_type {};
template<> struct is_uint8_vector<u8x2> : std::true_type {};
template<> struct is_uint8_vector<u8x3> : std::true_type {};
template<> struct is_uint8_vector<u8x4> : std::true_type {};
template<> struct is_uint8_vector<u8x8> : std::true_type {};
template<> struct is_uint8_vector<u8x16> : std::true_type {};
template<> struct is_uint8_vector<u8x32> : std::true_type {};
template<> struct is_uint8_vector<u8x64> : std::true_type {};

// Specializations for 16-bit vectors
template<> struct is_uint16_vector<u16x1> : std::true_type {};
template<> struct is_uint16_vector<u16x2> : std::true_type {};
template<> struct is_uint16_vector<u16x3> : std::true_type {};
template<> struct is_uint16_vector<u16x4> : std::true_type {};
template<> struct is_uint16_vector<u16x8> : std::true_type {};
template<> struct is_uint16_vector<u16x16> : std::true_type {};
template<> struct is_uint16_vector<u16x32> : std::true_type {};

// Specializations for 32-bit vectors
template<> struct is_uint32_vector<u32x1> : std::true_type {};
template<> struct is_uint32_vector<u32x2> : std::true_type {};
template<> struct is_uint32_vector<u32x3> : std::true_type {};
template<> struct is_uint32_vector<u32x4> : std::true_type {};
template<> struct is_uint32_vector<u32x8> : std::true_type {};
template<> struct is_uint32_vector<u32x16> : std::true_type {};

// Specializations for 64-bit vectors
template<> struct is_uint64_vector<u64x1> : std::true_type {};
template<> struct is_uint64_vector<u64x2> : std::true_type {};
template<> struct is_uint64_vector<u64x3> : std::true_type {};
template<> struct is_uint64_vector<u64x4> : std::true_type {};
template<> struct is_uint64_vector<u64x8> : std::true_type {};

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

inline position pointInSquare(u32x3 &seeds){
    constexpr position conversion = {INV_INT_MAX_F, INV_INT_MAX_F, 0.0f};
    pcgHash(seeds);
    return simd_muladd(simd_float3(seeds), conversion, -1.0f);
}
