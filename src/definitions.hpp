#pragma once
#include <cstdint>
#include <simd/simd.h>

using ui8 = uint8_t;
using ui16 = uint16_t;
using ui32 = uint32_t;
using ui64 = uint64_t;

using si8 = int8_t;
using si16 = int16_t;
using si32 = int32_t;
using si64 = int64_t;

using fp16 = __fp16;
using fp32 = float;
using fp64 = double;
using fp128 = long double;

// Apple SIMD vector types

// Unsigned integers
using ui8x1 = simd_uchar1;
using ui8x2 = simd_uchar2;
using ui8x3 = simd_uchar3;
using ui8x4 = simd_uchar4;
using ui8x8 = simd_uchar8;
using ui8x16 = simd_uchar16;
using ui8x32 = simd_uchar32;
using ui8x64 = simd_uchar64;

using ui16x1 = simd_ushort1;
using ui16x2 = simd_ushort2;
using ui16x3 = simd_ushort3;
using ui16x4 = simd_ushort4;
using ui16x8 = simd_ushort8;
using ui16x16 = simd_ushort16;
using ui16x32 = simd_ushort32;

using ui32x1 = simd_uint1;
using ui32x2 = simd_uint2;
using ui32x3 = simd_uint3;
using ui32x4 = simd_uint4;
using ui32x8 = simd_uint8;
using ui32x16 = simd_uint16;

using ui64x1 = simd_ulong1;
using ui64x2 = simd_ulong2;
using ui64x3 = simd_ulong3;
using ui64x4 = simd_ulong4;
using ui64x8 = simd_ulong8;

// Signed integer
using si8x1 = simd_char1;
using si8x2 = simd_char2;
using si8x3 = simd_char3;
using si8x4 = simd_char4;
using si8x8 = simd_char8;
using si8x16 = simd_char16;
using si8x32 = simd_char32;
using si8x64 = simd_char64;

using si16x1 = simd_short1;
using si16x2 = simd_short2;
using si16x3 = simd_short3;
using si16x4 = simd_short4;
using si16x8 = simd_short8;
using si16x16 = simd_short16;
using si16x32 = simd_short32;

using si32x1 = simd_int1;
using si32x2 = simd_int2;
using si32x3 = simd_int3;
using si32x4 = simd_int4;
using si32x8 = simd_int8;
using si32x16 = simd_int16;

using si64x1 = simd_long1;
using si64x2 = simd_long2;
using si64x3 = simd_long3;
using si64x4 = simd_long4;
using si64x8 = simd_long8;

// Floating points
using fp16x1 = simd_half1;
using fp16x2 = simd_half2;
using fp16x3 = simd_half3;
using fp16x4 = simd_half4;
using fp16x8 = simd_half8;
using fp16x16 = simd_half16;
using fp16x32 = simd_half32;

using fp32x1 = simd_float1;
using fp32x2 = simd_float2;
using fp32x3 = simd_float3;
using fp32x4 = simd_float4;
using fp32x8 = simd_float8;
using fp32x16 = simd_float16;

using fp64x1 = simd_double1;
using fp64x2 = simd_double2;
using fp64x3 = simd_double3;
using fp64x4 = simd_double4;
using fp64x8 = simd_double8;

// Aliases

using position = fp32x3;
using unitVec = fp32x3;
using colorF = fp32x3;
using colorU = ui8x3;
using m3x2 = simd_float3x2;
using m3x3 = simd_float3x3;
using m3x4 = simd_float3x4;

// Avoiding namespace pollution for basic vector math

using simd::dot;
using simd::cross;
using simd::fma;
using simd::normalize;
using simd::reflect;
using simd::refract;
