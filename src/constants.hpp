#pragma once
#include "definitions.hpp"

// Mathematical constants

constexpr fp32 PI = 3.1415926535897f;
constexpr fp32 TAU = 2.0f * PI;
constexpr fp32 HALF_PI = 0.5f * PI;
constexpr fp32 PI_INV = 1.0 / PI;
constexpr fp32 TAU_INV = 1.0 / TAU;
constexpr fp32 EPSILON = 1e-6f;
constexpr fp32 MIN_DISTANCE = 1.0;
constexpr fp32 INFINITY_F = std::numeric_limits<fp32>::infinity();
constexpr fp32 INT_MAX_F = 0x1.0p31;
constexpr fp32 INV_INT_MAX_F = 0x1.0p-31;
constexpr fp32 UINT_MAX_F = 0x1.0p32;
constexpr fp32 INV_UINT_MAX_F = 0x1.0p-32;

constexpr ui32 UINT_MAX_U = 0xFFFFFFFF;
constexpr si32 INT_MAX_I = 0x7FFFFFFF;
