#pragma once

#define PI 3.14159265358979323846f
#define SQRT_TWO 1.41421356237309504880f
#define SQRT_THREE 1.73205080756887729352f

#define DEG2RADMUL (PI / 180.0f)
#define DEG2RAD(x) ((x) * DEG2RADMUL)
#define RAD2DEGMUL (180.0f / PI)
#define RAD2DEG(x) ((x) * (180.0f / PI))

#define FLOAT_EPSILON 1.192092896e-07f
#define FLOAT_MIN -3.40282e+38F
#define FLOAT_MAX 3.40282e+38F

#include <defines.h>

#define __define_vec2(T, name) typedef union _##T##name { struct { T x, y; }; struct { T s, t; }; struct { T r, g; }; struct { T u, v; }; T data[2]; } ##name
#define __define_vec3(T, name) typedef union _##T##name { struct { T x, y, z; }; struct { T s, t, p; }; struct { T r, g, b; }; struct { T u, v, w; }; T data[3]; } ##name
#define __define_vec4(T, name) typedef union _##T##name { struct { T x, y, z, w; }; struct { T s, t, p, q; }; struct { T r, g, b, a; }; T data[4]; } ##name

#define __define_vec2_create(TRET, T, name) INLINE TRET name##_create(T x, T y) { TRET result; result.x = x; result.y = y; return result; }
#define __define_vec3_create(TRET, T, name) INLINE TRET name##_create(T x, T y, T z) { TRET result; result.x = x; result.y = y; result.z = z; return result; }
#define __define_vec4_create(TRET, T, name) INLINE TRET name##_create(T x, T y, T z, T w) { TRET result; result.x = x; result.y = y; result.z = z; result.w = w; return result; }

#define __define_vec2_zero(TRET, name) INLINE TRET name##_zero() { return (TRET){0.0f, 0.0f}; }
#define __define_vec3_zero(TRET, name) INLINE TRET name##_zero() { return (TRET){0.0f, 0.0f, 0.0f}; }
#define __define_vec4_zero(TRET, name) INLINE TRET name##_zero() { return (TRET){0.0f, 0.0f, 0.0f, 0.0f}; }

#define __define_vec2_one(TRET, name) INLINE TRET name##_one() { return (TRET){1.0f, 1.0f}; }
#define __define_vec3_one(TRET, name) INLINE TRET name##_one() { return (TRET){1.0f, 1.0f, 1.0f}; }
#define __define_vec4_one(TRET, name) INLINE TRET name##_one() { return (TRET){1.0f, 1.0f, 1.0f, 1.0f}; }

#define __define_vec2_up(TRET, name) INLINE TRET name##_up() { return (TRET){0.0f, 1.0f}; }
#define __define_vec3_up(TRET, name) INLINE TRET name##_up() { return (TRET){0.0f, 1.0f, 0.0f}; }
#define __define_vec4_up(TRET, name) INLINE TRET name##_up() { return (TRET){0.0f, 1.0f, 0.0f, 0.0f}; }

#define __define_vec2_down(TRET, name) INLINE TRET name##_down() { return (TRET){0.0f, -1.0f}; }
#define __define_vec3_down(TRET, name) INLINE TRET name##_down() { return (TRET){0.0f, -1.0f, 0.0f}; }
#define __define_vec4_down(TRET, name) INLINE TRET name##_down() { return (TRET){0.0f, -1.0f, 0.0f, 0.0f}; }

#define __define_vec2_left(TRET, name) INLINE TRET name##_left() { return (TRET){-1.0f, 0.0f}; }
#define __define_vec3_left(TRET, name) INLINE TRET name##_left() { return (TRET){-1.0f, 0.0f, 0.0f}; }
#define __define_vec4_left(TRET, name) INLINE TRET name##_left() { return (TRET){-1.0f, 0.0f, 0.0f, 0.0f}; }

#define __define_vec2_right(TRET, name) INLINE TRET name##_right() { return (TRET){1.0f, 0.0f}; }
#define __define_vec3_right(TRET, name) INLINE TRET name##_right() { return (TRET){1.0f, 0.0f, 0.0f}; }
#define __define_vec4_right(TRET, name) INLINE TRET name##_right() { return (TRET){1.0f, 0.0f, 0.0f, 0.0f}; }

#define __define_vec2_add(TRET, name) INLINE TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; return result; }
#define __define_vec3_add(TRET, name) INLINE TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; result.z = a.z + b.z; return result; }
#define __define_vec4_add(TRET, name) INLINE TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; result.z = a.z + b.z; result.w = a.w + b.w; return result; }

#define __define_vec2_sub(TRET, name) INLINE TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; return result; }
#define __define_vec3_sub(TRET, name) INLINE TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; result.z = a.z - b.z; return result; }
#define __define_vec4_sub(TRET, name) INLINE TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; result.z = a.z - b.z; result.w = a.w - b.w; return result; }

#define __define_vec2_mul(TRET, name) INLINE TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; return result; }
#define __define_vec3_mul(TRET, name) INLINE TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; result.z = a.z * b.z; return result; }
#define __define_vec4_mul(TRET, name) INLINE TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; result.z = a.z * b.z; result.w = a.w * b.w; return result; }

#define __define_vec2_mul_scalar(TRET, name) INLINE TRET name##_mul_scalar(TRET a, float b) { TRET result; result.x = a.x * b; result.y = a.y * b; return result; }
#define __define_vec3_mul_scalar(TRET, name) INLINE TRET name##_mul_scalar(TRET a, float b) { TRET result; result.x = a.x * b; result.y = a.y * b; result.z = a.z * b; return result; }
#define __define_vec4_mul_scalar(TRET, name) INLINE TRET name##_mul_scalar(TRET a, float b) { TRET result; result.x = a.x * b; result.y = a.y * b; result.z = a.z * b; result.w = a.w * b; return result; }

#define __define_vec2_mul_add(TRET, name) INLINE TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; return result; }
#define __define_vec3_mul_add(TRET, name) INLINE TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; result.z = a.z * b.z + c.z; return result; }
#define __define_vec4_mul_add(TRET, name) INLINE TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; result.z = a.z * b.z + c.z; result.w = a.w * b.w + c.w; return result; }

#define __define_vec2_div(TRET, name) INLINE TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; return result; }
#define __define_vec3_div(TRET, name) INLINE TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; result.z = a.z / b.z; return result; }
#define __define_vec4_div(TRET, name) INLINE TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; result.z = a.z / b.z; result.w = a.w / b.w; return result; }

#define __define_vec2_length_sq(T, TRET, name) INLINE TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y; }
#define __define_vec3_length_sq(T, TRET, name) INLINE TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
#define __define_vec4_length_sq(T, TRET, name) INLINE TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }

#define __define_vec2_length(T, TRET, name) INLINE TRET name##_length(T a) { return wsqrt(a.x * a.x + a.y * a.y); }
#define __define_vec3_length(T, TRET, name) INLINE TRET name##_length(T a) { return wsqrt(a.x * a.x + a.y * a.y + a.z * a.z); }
#define __define_vec4_length(T, TRET, name) INLINE TRET name##_length(T a) { return wsqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w); }

#define __define_vec2_all(TRET, T, name) __define_vec2(T, name); __define_vec2_create(TRET, T, name); __define_vec2_zero(TRET, name); __define_vec2_one(TRET, name); __define_vec2_up(TRET, name); __define_vec2_down(TRET, name); __define_vec2_left(TRET, name); __define_vec2_right(TRET, name); __define_vec2_add(TRET, name); __define_vec2_sub(TRET, name); __define_vec2_mul(TRET, name); __define_vec2_mul_scalar(TRET, name); __define_vec2_mul_add(TRET, name); __define_vec2_div(TRET, name); __define_vec2_length_sq(TRET, T, name); __define_vec2_length(TRET, T, name);
#define __define_vec3_all(TRET, T, name) __define_vec3(T, name); __define_vec3_create(TRET, T, name); __define_vec3_zero(TRET, name); __define_vec3_one(TRET, name); __define_vec3_up(TRET, name); __define_vec3_down(TRET, name); __define_vec3_left(TRET, name); __define_vec3_right(TRET, name); __define_vec3_add(TRET, name); __define_vec3_sub(TRET, name); __define_vec3_mul(TRET, name); __define_vec3_mul_scalar(TRET, name); __define_vec3_mul_add(TRET, name); __define_vec3_div(TRET, name); __define_vec3_length_sq(TRET, T, name); __define_vec3_length(TRET, T, name);
#define __define_vec4_all(TRET, T, name) __define_vec4(T, name); __define_vec4_create(TRET, T, name); __define_vec4_zero(TRET, name); __define_vec4_one(TRET, name); __define_vec4_up(TRET, name); __define_vec4_down(TRET, name); __define_vec4_left(TRET, name); __define_vec4_right(TRET, name); __define_vec4_add(TRET, name); __define_vec4_sub(TRET, name); __define_vec4_mul(TRET, name); __define_vec4_mul_scalar(TRET, name); __define_vec4_mul_add(TRET, name); __define_vec4_div(TRET, name); __define_vec4_length_sq(TRET, T, name); __define_vec4_length(TRET, T, name);

__define_vec2_all(vec2, float, vec2);
__define_vec2_all(vec2d, double, vec2d);
__define_vec2_all(vec2u, uint32_t, vec2u);
__define_vec2_all(vec2i, int32_t, vec2i);

__define_vec3_all(vec3, float, vec3);
__define_vec3_all(vec3d, double, vec3d);
__define_vec3_all(vec3u, uint32_t, vec3u);
__define_vec3_all(vec3i, int32_t, vec3i);

__define_vec4_all(vec4, float, vec4);
__define_vec4_all(vec4d, double, vec4d);
__define_vec4_all(vec4u, uint32_t, vec4u);
__define_vec4_all(vec4i, int32_t, vec4i);

#define SWAP(T, a, b) { T tmp = a; a = b; b = tmp; }


WAG_API float wsin(float x);
WAG_API float wcos(float x);
WAG_API float wtan(float x);
WAG_API float wctg(float x);
WAG_API float wacos(float x);
WAG_API float wasin(float x);
WAG_API float watan(float x);
WAG_API float wactg(float x);

WAG_API float wsqrt(float x);
WAG_API float wabs(float x);
WAG_API float wfloor(float x);
WAG_API float wceil(float x);
WAG_API float wlog2(float x);
WAG_API float wpow(float x, float y);

WAG_API int32_t wrandom();
WAG_API float wfrandom();

WAG_API float wfrandom_range(float min, float max);


INLINE bool wispow2(uint64_t val) { return (val != 0) && ((val & (val - 1)) == 0); }
INLINE float wsign(float x) { return x == 0.0f ? 0.0f : x < 0.0f ? -1.0f : 1.0f; }
INLINE bool wfloat_cmp(float a, float b) { wabs(a - b) < FLOAT_EPSILON; }

