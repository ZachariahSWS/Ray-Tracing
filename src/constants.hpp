#pragma once
#include "definitions.hpp"

// Mathematical constants

constexpr f32 PI = 3.1415926535897f;
constexpr f32 TAU = 2.0f * PI;
constexpr f32 HALF_PI = 0.5f * PI;
constexpr f32 PI_INV = 1.0 / PI;
constexpr f32 TAU_INV = 1.0 / TAU;
constexpr f32 EPSILON = 1e-6f;
constexpr f32 MIN_DISTANCE = 1.0;
constexpr f32 INFINITY_F = std::numeric_limits<f32>::infinity();
constexpr f32 INT_MAX_F = 0x1.0p31;
constexpr f32 INV_INT_MAX_F = 0x1.0p-31;
constexpr f32 UINT_MAX_F = 0x1.0p32;
constexpr f32 UINV_INT_MAX_F = 0x1.0p-32;

constexpr u32 UINT_MAX_U = 0xFFFFFFFF;
constexpr i32 INT_MAX_I = 0x7FFFFFFF;
