#pragma once
#include <cstdint>
#include <simd/simd.h>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;
using f128 = long double;

// Apple SIMD vector types

// Unsigned integers
using u8x1 = simd_uchar1;
using u8x2 = simd_uchar2;
using u8x3 = simd_uchar3;
using u8x4 = simd_uchar4;
using u8x8 = simd_uchar8;
using u8x16 = simd_uchar16;
using u8x32 = simd_uchar32;
using u8x64 = simd_uchar64;

using u16x1 = simd_ushort1;
using u16x2 = simd_ushort2;
using u16x3 = simd_ushort3;
using u16x4 = simd_ushort4;
using u16x8 = simd_ushort8;
using u16x16 = simd_ushort16;
using u16x32 = simd_ushort32;

using u32x1 = simd_uint1;
using u32x2 = simd_uint2;
using u32x3 = simd_uint3;
using u32x4 = simd_uint4;
using u32x8 = simd_uint8;
using u32x16 = simd_uint16;

using u64x1 = simd_ulong1;
using u64x2 = simd_ulong2;
using u64x3 = simd_ulong3;
using u64x4 = simd_ulong4;
using u64x8 = simd_ulong8;

// Signed integer
using i8x1 = simd_char1;
using i8x2 = simd_char2;
using i8x3 = simd_char3;
using i8x4 = simd_char4;
using i8x8 = simd_char8;
using i8x16 = simd_char16;
using i8x32 = simd_char32;
using i8x64 = simd_char64;

using i16x1 = simd_short1;
using i16x2 = simd_short2;
using i16x3 = simd_short3;
using i16x4 = simd_short4;
using i16x8 = simd_short8;
using i16x16 = simd_short16;
using i16x32 = simd_short32;

using i32x1 = simd_int1;
using i32x2 = simd_int2;
using i32x3 = simd_int3;
using i32x4 = simd_int4;
using i32x8 = simd_int8;
using i32x16 = simd_int16;

using i64x1 = simd_long1;
using i64x2 = simd_long2;
using i64x3 = simd_long3;
using i64x4 = simd_long4;
using i64x8 = simd_long8;

// Floating points
using f16x1 = simd_half1;
using f16x2 = simd_half2;
using f16x3 = simd_half3;
using f16x4 = simd_half4;
using f16x8 = simd_half8;
using f16x16 = simd_half16;
using f16x32 = simd_half32;

using f32x1 = simd_float1;
using f32x2 = simd_float2;
using f32x3 = simd_float3;
using f32x4 = simd_float4;
using f32x8 = simd_float8;
using f32x16 = simd_float16;

using f64x1 = simd_double1;
using f64x2 = simd_double2;
using f64x3 = simd_double3;
using f64x4 = simd_double4;
using f64x8 = simd_double8;

// Aliases

using Vec3 = f32x3;
using Normal3 = f32x3;
using ColorF = f32x3;
using ColorU = u8x3;
using m3x2 = simd_float3x2;
using m3x3 = simd_float3x3;
using m3x4 = simd_float3x4;

// Mathematical constants

constexpr f32 PI = 3.1415926535897f;
constexpr f32 TAU = 2.0f * PI;
constexpr f32 HALF_PI = 0.5f * PI;
constexpr f32 PI_INV = 1.0 / PI;
constexpr f32 TAU_INV = 1.0 / TAU;
constexpr f32 EPSILON = 1e-6f;
constexpr f32 INFINITY_F = std::numeric_limits<f32>::infinity();

// Avoiding namespace pollution for basic vector math

using simd::dot;
using simd::cross;
using simd::fma;
using simd::normalize;
using simd::reflect;
using simd::refract;
