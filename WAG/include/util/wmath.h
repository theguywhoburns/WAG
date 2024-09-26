#pragma once

#include <pp_util.h>

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

#define WMIN(x, y) ((x) < (y) ? (x) : (y))
#define WMAX(x, y) ((x) > (y) ? (x) : (y))

#define SWAP(T, a, b) { T tmp = a; a = b; b = tmp; }

WAG_API double wsin(double x);
WAG_API double wcos(double x);
WAG_API double wtan(double x);
WAG_API double wctg(double x);
WAG_API double wacos(double x);
WAG_API double wasin(double x);
WAG_API double watan(double x);
WAG_API double wactg(double x);

WAG_API double wsqrt(double x);
WAG_API double wabs(double x);
WAG_API double wfloor(double x);
WAG_API double wceil(double x);
WAG_API double wlog2(double x);
WAG_API double wpow(double x, double y);

WAG_API int32_t wrandom();
WAG_API double wfrandom();

WAG_API double wfrandom_range(double min, double max);

WAG_API double wsign(double x);	

#define wispow2(val) ((val != 0) && ((val & (val - 1)) == 0))
#define wsign(x) (return x == 0.0f ? 0.0f : x < 0.0f ? -1.0f : 1.0f)
#define wfloat_cmp(a, b) ((float)wabs(a - b) < FLOAT_EPSILON)
#define wdouble_cmp(a, b) (wabs(a - b) < FLOAT_EPSILON)

// For vector comparisons
#define __float_compare(a, b) wfloat_cmp(a, b)
#define __double_compare(a, b) wdouble_cmp(a, b)
#define __uint32_t_compare(a, b) a == b
#define __int32_t_compare(a, b)  a == b

// TODO: Stop writing code while on crack

#pragma region MacrosThatIWroteLikeanInsanePerson
#pragma region VectorMacros
#define __define_vec2(T, name) typedef union _##T##name { struct { T x, y; }; struct { T s, t; }; struct { T r, g; }; struct { T u, v; }; T data[2]; } name
#define __define_vec3(T, name) typedef union _##T##name { struct { T x, y, z; }; struct { T s, t, p; }; struct { T r, g, b; }; struct { T u, v, w; }; T data[3]; } name
#define __define_vec4(T, name) typedef union _##T##name { struct { T x, y, z, w; }; struct { T s, t, p, q; }; struct { T r, g, b, a; }; T data[4]; } name

#define __define_vec2_create(TRET, T, name) TRET name##_create(T x, T y);
#define __define_vec2_create_impl(TRET, T, name) TRET name##_create(T x, T y) { TRET result; result.x = x; result.y = y; return result; }
#define __define_vec3_create(TRET, T, name) TRET name##_create(T x, T y, T z);
#define __define_vec3_create_impl(TRET, T, name) TRET name##_create(T x, T y, T z) { TRET result; result.x = x; result.y = y; result.z = z; return result; }
#define __define_vec4_create(TRET, T, name) TRET name##_create(T x, T y, T z, T w);
#define __define_vec4_create_impl(TRET, T, name) TRET name##_create(T x, T y, T z, T w) { TRET result; result.x = x; result.y = y; result.z = z; result.w = w; return result; }

#define __define_vec2_zero(TRET, T, name) TRET name##_zero();
#define __define_vec2_zero_impl(TRET, T, name) TRET name##_zero() { return (TRET){(T)0.0f, (T)0.0f}; }
#define __define_vec3_zero(TRET, T, name) TRET name##_zero();
#define __define_vec3_zero_impl(TRET, T, name) TRET name##_zero() { return (TRET){(T)0.0f, (T)0.0f, (T)0.0f}; }
#define __define_vec4_zero(TRET, T, name) TRET name##_zero();
#define __define_vec4_zero_impl(TRET, T, name) TRET name##_zero() { return (TRET){(T)0.0f, (T)0.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_one(TRET, T, name) TRET name##_one();
#define __define_vec2_one_impl(TRET, T, name) TRET name##_one() { return (TRET){(T)1.0f, (T)1.0f}; }
#define __define_vec3_one(TRET, T, name) TRET name##_one();
#define __define_vec3_one_impl(TRET, T, name) TRET name##_one() { return (TRET){(T)1.0f, (T)1.0f, (T)1.0f}; }
#define __define_vec4_one(TRET, T, name) TRET name##_one();
#define __define_vec4_one_impl(TRET, T, name) TRET name##_one() { return (TRET){(T)1.0f, (T)1.0f, (T)1.0f, (T)1.0f}; }

#define __define_vec2_up(TRET, T, name) TRET name##_up();
#define __define_vec2_up_impl(TRET, T, name) TRET name##_up() { return (TRET){(T)0.0f, (T)1.0f}; }
#define __define_vec3_up(TRET, T, name) TRET name##_up();
#define __define_vec3_up_impl(TRET, T, name) TRET name##_up() { return (TRET){(T)0.0f, (T)1.0f, (T)0.0f}; }
#define __define_vec4_up(TRET, T, name) TRET name##_up();
#define __define_vec4_up_impl(TRET, T, name) TRET name##_up() { return (TRET){(T)0.0f, (T)1.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_down(TRET, T, name) TRET name##_down();
#define __define_vec2_down_impl(TRET, T, name) TRET name##_down() { return (TRET){(T)0.0f, (T)-1.0f}; }
#define __define_vec3_down(TRET, T, name) TRET name##_down();
#define __define_vec3_down_impl(TRET, T, name) TRET name##_down() { return (TRET){(T)0.0f, (T)-1.0f, (T)0.0f}; }
#define __define_vec4_down(TRET, T, name) TRET name##_down();
#define __define_vec4_down_impl(TRET, T, name) TRET name##_down() { return (TRET){(T)0.0f, (T)-1.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_left(TRET, T, name) TRET name##_left();
#define __define_vec2_left_impl(TRET, T, name) TRET name##_left() { return (TRET){(T)-1.0f, (T)0.0f}; }
#define __define_vec3_left(TRET, T, name) TRET name##_left();
#define __define_vec3_left_impl(TRET, T, name) TRET name##_left() { return (TRET){(T)-1.0f, (T)0.0f, (T)0.0f}; }
#define __define_vec4_left(TRET, T, name) TRET name##_left();
#define __define_vec4_left_impl(TRET, T, name) TRET name##_left() { return (TRET){(T)-1.0f, (T)0.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_right(TRET, T, name) TRET name##_right();
#define __define_vec2_right_impl(TRET, T, name) TRET name##_right() { return (TRET){(T)1.0f, (T)0.0f}; }
#define __define_vec3_right(TRET, T, name) TRET name##_right();
#define __define_vec3_right_impl(TRET, T, name) TRET name##_right() { return (TRET){(T)1.0f, (T)0.0f, (T)0.0f}; }
#define __define_vec4_right(TRET, T, name) TRET name##_right();
#define __define_vec4_right_impl(TRET, T, name) TRET name##_right() { return (TRET){(T)1.0f, (T)0.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_add(TRET, name) TRET name##_add(TRET a, TRET b);
#define __define_vec2_add_impl(TRET, name) TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; return result; }
#define __define_vec3_add(TRET, name) TRET name##_add(TRET a, TRET b);
#define __define_vec3_add_impl(TRET, name) TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; result.z = a.z + b.z; return result; }
#define __define_vec4_add(TRET, name) TRET name##_add(TRET a, TRET b);
#define __define_vec4_add_impl(TRET, name) TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; result.z = a.z + b.z; result.w = a.w + b.w; return result; }

#define __define_vec2_sub(TRET, name) TRET name##_sub(TRET a, TRET b);
#define __define_vec2_sub_impl(TRET, name) TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; return result; }
#define __define_vec3_sub(TRET, name) TRET name##_sub(TRET a, TRET b);
#define __define_vec3_sub_impl(TRET, name) TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; result.z = a.z - b.z; return result; }
#define __define_vec4_sub(TRET, name) TRET name##_sub(TRET a, TRET b);
#define __define_vec4_sub_impl(TRET, name) TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; result.z = a.z - b.z; result.w = a.w - b.w; return result; }

#define __define_vec2_mul(TRET, name) TRET name##_mul(TRET a, TRET b);
#define __define_vec2_mul_impl(TRET, name) TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; return result; }
#define __define_vec3_mul(TRET, name) TRET name##_mul(TRET a, TRET b);
#define __define_vec3_mul_impl(TRET, name) TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; result.z = a.z * b.z; return result; }
#define __define_vec4_mul(TRET, name) TRET name##_mul(TRET a, TRET b);
#define __define_vec4_mul_impl(TRET, name) TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; result.z = a.z * b.z; result.w = a.w * b.w; return result; }

#define __define_vec2_mul_scalar(TRET, T, name) TRET name##_mul_scalar(TRET a, T b);
#define __define_vec2_mul_scalar_impl(TRET, T, name) TRET name##_mul_scalar(TRET a, T b) { TRET result; result.x = a.x * b; result.y = a.y * b; return result; }
#define __define_vec3_mul_scalar(TRET, T, name) TRET name##_mul_scalar(TRET a, T b);
#define __define_vec3_mul_scalar_impl(TRET, T, name) TRET name##_mul_scalar(TRET a, T b) { TRET result; result.x = a.x * b; result.y = a.y * b; result.z = a.z * b; return result; }
#define __define_vec4_mul_scalar(TRET, T, name) TRET name##_mul_scalar(TRET a, T b);
#define __define_vec4_mul_scalar_impl(TRET, T, name) TRET name##_mul_scalar(TRET a, T b) { TRET result; result.x = a.x * b; result.y = a.y * b; result.z = a.z * b; result.w = a.w * b; return result; }

#define __define_vec2_mul_add(TRET, name) TRET name##_mul_add(TRET a, TRET b, TRET c);
#define __define_vec2_mul_add_impl(TRET, name) TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; return result; }
#define __define_vec3_mul_add(TRET, name) TRET name##_mul_add(TRET a, TRET b, TRET c);
#define __define_vec3_mul_add_impl(TRET, name) TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; result.z = a.z * b.z + c.z; return result; }
#define __define_vec4_mul_add(TRET, name) TRET name##_mul_add(TRET a, TRET b, TRET c);
#define __define_vec4_mul_add_impl(TRET, name) TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; result.z = a.z * b.z + c.z; result.w = a.w * b.w + c.w; return result; }
 
#define __define_vec2_div(TRET, name) TRET name##_div(TRET a, TRET b);
#define __define_vec2_div_impl(TRET, name) TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; return result; }
#define __define_vec3_div(TRET, name) TRET name##_div(TRET a, TRET b);
#define __define_vec3_div_impl(TRET, name) TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; result.z = a.z / b.z; return result; }
#define __define_vec4_div(TRET, name) TRET name##_div(TRET a, TRET b);
#define __define_vec4_div_impl(TRET, name) TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; result.z = a.z / b.z; result.w = a.w / b.w; return result; }

#define __define_vec2_length_sq(T, TRET, name) TRET name##_length_sq(T a);
#define __define_vec2_length_sq_impl(T, TRET, name) TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y; }
#define __define_vec3_length_sq(T, TRET, name) TRET name##_length_sq(T a);
#define __define_vec3_length_sq_impl(T, TRET, name) TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
#define __define_vec4_length_sq(T, TRET, name) TRET name##_length_sq(T a);
#define __define_vec4_length_sq_impl(T, TRET, name) TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }

#define __define_vec2_length(T, TRET, name) TRET name##_length(T a);
#define __define_vec2_length_impl(T, TRET, name) TRET name##_length(T a) { return (TRET)wsqrt(a.x * a.x + a.y * a.y); }
#define __define_vec3_length(T, TRET, name) TRET name##_length(T a);
#define __define_vec3_length_impl(T, TRET, name) TRET name##_length(T a) { return (TRET)wsqrt(a.x * a.x + a.y * a.y + a.z * a.z); }
#define __define_vec4_length(T, TRET, name) TRET name##_length(T a);
#define __define_vec4_length_impl(T, TRET, name) TRET name##_length(T a) { return (TRET)wsqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w); }

#define __define_vec2_normalize(TRET, T, name) void name##_normalize(TRET* a);
#define __define_vec2_normalize_impl(TRET, T, name) void name##_normalize(TRET* a) { const T len = name##_length(*a); a->x /= len; a->y /= len; }
#define __define_vec3_normalize(TRET, T, name) void name##_normalize(TRET* a);
#define __define_vec3_normalize_impl(TRET, T, name) void name##_normalize(TRET* a) { const T len = name##_length(*a); a->x /= len; a->y /= len; a->z /= len; }
#define __define_vec4_normalize(TRET, T, name) void name##_normalize(TRET* a);
#define __define_vec4_normalize_impl(TRET, T, name) void name##_normalize(TRET* a) { const T len = name##_length(*a); a->x /= len; a->y /= len; a->z /= len; a->w /= len; }

#define __define_vec2_normalized(TRET, T, name) TRET name##_normalized(TRET a);
#define __define_vec2_normalized_impl(TRET, T, name) TRET name##_normalized(TRET a) { name##_normalize(&a); return a; }
#define __define_vec3_normalized(TRET, T, name) TRET name##_normalized(TRET a);
#define __define_vec3_normalized_impl(TRET, T, name) TRET name##_normalized(TRET a) { name##_normalize(&a); return a; }
#define __define_vec4_normalized(TRET, T, name) TRET name##_normalized(TRET a);
#define __define_vec4_normalized_impl(TRET, T, name) TRET name##_normalized(TRET a) { name##_normalize(&a); return a; }

#define __define_vec2_dot(TRET, T, name) T name##_dot(TRET a, TRET b);
#define __define_vec2_dot_impl(TRET, T, name) T name##_dot(TRET a, TRET b) { return a.x * b.x + a.y * b.y; }
#define __define_vec3_dot(TRET, T, name) T name##_dot(TRET a, TRET b);
#define __define_vec3_dot_impl(TRET, T, name) T name##_dot(TRET a, TRET b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
#define __define_vec4_dot(TRET, T, name) T name##_dot(TRET a, TRET b);
#define __define_vec4_dot_impl(TRET, T, name) T name##_dot(TRET a, TRET b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

#define __define_vec2_compare(TRET, T, name) bool name##_compare(TRET a, TRET b);
#define __define_vec2_compare_impl(TRET, T, name) bool name##_compare(TRET a, TRET b) { return __##T##_compare(a.x, b.x) && __##T##_compare(a.y, b.y); }
#define __define_vec3_compare(TRET, T, name) bool name##_compare(TRET a, TRET b);
#define __define_vec3_compare_impl(TRET, T, name) bool name##_compare(TRET a, TRET b) { return __##T##_compare(a.x, b.x) && __##T##_compare(a.y, b.y) && __##T##_compare(a.z, b.z); }
#define __define_vec4_compare(TRET, T, name) bool name##_compare(TRET a, TRET b);
#define __define_vec4_compare_impl(TRET, T, name) bool name##_compare(TRET a, TRET b) { return __##T##_compare(a.x, b.x) && __##T##_compare(a.y, b.y) && __##T##_compare(a.z, b.z) && __##T##_compare(a.w, b.w); }

#define __define_vec2_min(TRET, T, name) TRET name##_min(TRET a, TRET b);
#define __define_vec2_min_impl(TRET, T, name) TRET name##_min(TRET a, TRET b) { return name##_create(WMIN(a.x, b.x), WMIN(a.y, b.y)); }
#define __define_vec3_min(TRET, T, name) TRET name##_min(TRET a, TRET b);
#define __define_vec3_min_impl(TRET, T, name) TRET name##_min(TRET a, TRET b) { return name##_create(WMIN(a.x, b.x), WMIN(a.y, b.y), WMIN(a.z, b.z)); }
#define __define_vec4_min(TRET, T, name) TRET name##_min(TRET a, TRET b);
#define __define_vec4_min_impl(TRET, T, name) TRET name##_min(TRET a, TRET b) { return name##_create(WMIN(a.x, b.x), WMIN(a.y, b.y), WMIN(a.z, b.z), WMIN(a.w, b.w)); }

#define __define_vec2_max(TRET, T, name) TRET name##_max(TRET a, TRET b);
#define __define_vec2_max_impl(TRET, T, name) TRET name##_max(TRET a, TRET b) { return name##_create(WMAX(a.x, b.x), WMAX(a.y, b.y)); }
#define __define_vec3_max(TRET, T, name) TRET name##_max(TRET a, TRET b);
#define __define_vec3_max_impl(TRET, T, name) TRET name##_max(TRET a, TRET b) { return name##_create(WMAX(a.x, b.x), WMAX(a.y, b.y), WMAX(a.z, b.z)); }
#define __define_vec4_max(TRET, T, name) TRET name##_max(TRET a, TRET b);
#define __define_vec4_max_impl(TRET, T, name) TRET name##_max(TRET a, TRET b) { return name##_create(WMAX(a.x, b.x), WMAX(a.y, b.y), WMAX(a.z, b.z), WMAX(a.w, b.w)); }

#define __define_vec2_sign(TRET, T, name) TRET name##_sign(TRET a);
#define __define_vec2_sign_impl(TRET, T, name) TRET name##_sign(TRET a) { return name##_create((T)sign((double)a.x), (T)sign((double)a.y)); }
#define __define_vec3_sign(TRET, T, name) TRET name##_sign(TRET a);
#define __define_vec3_sign_impl(TRET, T, name) TRET name##_sign(TRET a) { return name##_create((T)sign((double)a.x), (T)sign((double)a.y), (T)sign((double)a.z)); }
#define __define_vec4_sign(TRET, T, name) TRET name##_sign(TRET a);
#define __define_vec4_sign_impl(TRET, T, name) TRET name##_sign(TRET a) { return name##_create((T)sign((double)a.x), (T)sign((double)a.y), (T)sign((double)a.z), (T)sign((double)a.w)); }

#define __define_vec2_all(TRET, T, name) __define_vec2(T, name); __define_vec2_create(TRET, T, name); __define_vec2_zero(TRET, T, name); __define_vec2_one(TRET, T, name); __define_vec2_up(TRET, T, name); __define_vec2_down(TRET, T, name); __define_vec2_left(TRET, T, name); __define_vec2_right(TRET, T, name); __define_vec2_add(TRET, name); __define_vec2_sub(TRET, name); __define_vec2_mul(TRET, name); __define_vec2_mul_scalar(TRET, T, name); __define_vec2_mul_add(TRET, name); __define_vec2_div(TRET, name); __define_vec2_length_sq(TRET, T, name); __define_vec2_length(TRET, T, name); __define_vec2_normalize(TRET, T, name); __define_vec2_normalized(TRET, T, name); __define_vec2_dot(TRET, T, name); __define_vec2_compare(TRET, T, name); __define_vec2_min(TRET, T, name); __define_vec2_max(TRET, T, name);
#define __define_vec2_all_impl(TRET, T, name)__define_vec2_create_impl(TRET, T, name); __define_vec2_zero_impl(TRET, T, name); __define_vec2_one_impl(TRET, T, name); __define_vec2_up_impl(TRET, T, name); __define_vec2_down_impl(TRET, T, name); __define_vec2_left_impl(TRET, T, name); __define_vec2_right_impl(TRET, T, name); __define_vec2_add_impl(TRET, name); __define_vec2_sub_impl(TRET, name); __define_vec2_mul_impl(TRET, name); __define_vec2_mul_scalar_impl(TRET, T, name); __define_vec2_mul_add_impl(TRET, name); __define_vec2_div_impl(TRET, name); __define_vec2_length_sq_impl(TRET, T, name); __define_vec2_length_impl(TRET, T, name); __define_vec2_normalize_impl(TRET, T, name); __define_vec2_normalized_impl(TRET, T, name); __define_vec2_dot_impl(TRET, T, name); __define_vec2_compare_impl(TRET, T, name); __define_vec2_min_impl(TRET, T, name); __define_vec2_max_impl(TRET, T, name);
#define __define_vec3_all(TRET, T, name) __define_vec3(T, name); __define_vec3_create(TRET, T, name); __define_vec3_zero(TRET, T, name); __define_vec3_one(TRET, T, name); __define_vec3_up(TRET, T, name); __define_vec3_down(TRET, T, name); __define_vec3_left(TRET, T, name); __define_vec3_right(TRET, T, name); __define_vec3_add(TRET, name); __define_vec3_sub(TRET, name); __define_vec3_mul(TRET, name); __define_vec3_mul_scalar(TRET, T, name); __define_vec3_mul_add(TRET, name); __define_vec3_div(TRET, name); __define_vec3_length_sq(TRET, T, name); __define_vec3_length(TRET, T, name); __define_vec3_normalize(TRET, T, name); __define_vec3_normalized(TRET, T, name); __define_vec3_dot(TRET, T, name); __define_vec3_compare(TRET, T, name); __define_vec3_min(TRET, T, name); __define_vec3_max(TRET, T, name);
#define __define_vec3_all_impl(TRET, T, name)__define_vec3_create_impl(TRET, T, name); __define_vec3_zero_impl(TRET, T, name); __define_vec3_one_impl(TRET, T, name); __define_vec3_up_impl(TRET, T, name); __define_vec3_down_impl(TRET, T, name); __define_vec3_left_impl(TRET, T, name); __define_vec3_right_impl(TRET, T, name); __define_vec3_add_impl(TRET, name); __define_vec3_sub_impl(TRET, name); __define_vec3_mul_impl(TRET, name); __define_vec3_mul_scalar_impl(TRET, T, name); __define_vec3_mul_add_impl(TRET, name); __define_vec3_div_impl(TRET, name); __define_vec3_length_sq_impl(TRET, T, name); __define_vec3_length_impl(TRET, T, name); __define_vec3_normalize_impl(TRET, T, name); __define_vec3_normalized_impl(TRET, T, name); __define_vec3_dot_impl(TRET, T, name); __define_vec3_compare_impl(TRET, T, name); __define_vec3_min_impl(TRET, T, name); __define_vec3_max_impl(TRET, T, name);
#define __define_vec4_all(TRET, T, name) __define_vec4(T, name); __define_vec4_create(TRET, T, name); __define_vec4_zero(TRET, T, name); __define_vec4_one(TRET, T, name); __define_vec4_up(TRET, T, name); __define_vec4_down(TRET, T, name); __define_vec4_left(TRET, T, name); __define_vec4_right(TRET, T, name); __define_vec4_add(TRET, name); __define_vec4_sub(TRET, name); __define_vec4_mul(TRET, name); __define_vec4_mul_scalar(TRET, T, name); __define_vec4_mul_add(TRET, name); __define_vec4_div(TRET, name); __define_vec4_length_sq(TRET, T, name); __define_vec4_length(TRET, T, name); __define_vec4_normalize(TRET, T, name); __define_vec4_normalized(TRET, T, name); __define_vec4_dot(TRET, T, name); __define_vec4_compare(TRET, T, name); __define_vec4_min(TRET, T, name); __define_vec4_max(TRET, T, name);
#define __define_vec4_all_impl(TRET, T, name)__define_vec4_create_impl(TRET, T, name); __define_vec4_zero_impl(TRET, T, name); __define_vec4_one_impl(TRET, T, name); __define_vec4_up_impl(TRET, T, name); __define_vec4_down_impl(TRET, T, name); __define_vec4_left_impl(TRET, T, name); __define_vec4_right_impl(TRET, T, name); __define_vec4_add_impl(TRET, name); __define_vec4_sub_impl(TRET, name); __define_vec4_mul_impl(TRET, name); __define_vec4_mul_scalar_impl(TRET, T, name); __define_vec4_mul_add_impl(TRET, name); __define_vec4_div_impl(TRET, name); __define_vec4_length_sq_impl(TRET, T, name); __define_vec4_length_impl(TRET, T, name); __define_vec4_normalize_impl(TRET, T, name); __define_vec4_normalized_impl(TRET, T, name); __define_vec4_dot_impl(TRET, T, name); __define_vec4_compare_impl(TRET, T, name); __define_vec4_min_impl(TRET, T, name); __define_vec4_max_impl(TRET, T, name);
#pragma endregion VectorMacros

#pragma region MatrixMacros

#define __define_mat(T, dim, name) typedef struct __##T##name {T data[dim*dim];} name
#define __define_mat_create(T, dim, name) name name##_create(T data[dim*dim]); 
#define __define_mat_create_impl(T, dim, name) name name##_create(T data[dim*dim]) { name out = {0}; for(size_t i = 0; i < dim*dim; ++i) { out.data[i] = data[i]; } return out; }
#define __define_mat_zero(T, dim, name) name name##_zero();
#define __define_mat_zero_impl(T, dim, name) name name##_zero() { return (name){(T){0}}; }
#define __define_mat_identity(T, dim, name) name name##_identity();
#define __define_mat_identity_impl(T, dim, name) name name##_identity() { name ret = name##_zero(); for(size_t i = 0; i < dim; ++i) { ret.data[i*dim+i] = 1; } return ret; } 
#define __define_mat_add(T, dim, name) name name##_add(name a, name b);
#define __define_mat_add_impl(T, dim, name) name name##_add(name a, name b) { name ret = name##_zero(); for(size_t i = 0; i < dim*dim; ++i) { ret.data[i] = a.data[i] + b.data[i]; } return ret; }
#define __define_mat_sub(T, dim, name) name name##_sub(name a, name b);
#define __define_mat_sub_impl(T, dim, name) name name##_sub(name a, name b) { name ret = name##_zero(); for(size_t i = 0; i < dim*dim; ++i) { ret.data[i] = a.data[i] - b.data[i]; } return ret; }
#define __define_mat_mul(T, dim, name) name name##_mul(name a, name b);
#define __define_mat_mul_impl(T, dim, name) name name##_mul(name a, name b) { name ret = name##_zero(); for(size_t i = 0; i < dim*dim; ++i) { ret.data[i] = a.data[i] * b.data[i]; } return ret; }
#define __define_mat_div(T, dim, name) name name##_div(name a, name b);
#define __define_mat_div_impl(T, dim, name) name name##_div(name a, name b) { name ret = name##_zero(); for(size_t i = 0; i < dim*dim; ++i) { ret.data[i] = a.data[i] / b.data[i]; } return ret; }

#define __define_mat_all(T, dim, name) \
  __define_mat(T, dim, name); \
  __define_mat_create(T, dim, name); \
  __define_mat_zero(T, dim, name); \
  __define_mat_identity(T, dim, name); \
  __define_mat_add(T, dim, name); \
  __define_mat_sub(T, dim, name); \
  __define_mat_mul(T, dim, name); \
  __define_mat_div(T, dim, name);

#define __define_mat_all_impl(T, dim, name) \
  __define_mat_create_impl(T, dim, name); \
  __define_mat_zero_impl(T, dim, name); \
  __define_mat_identity_impl(T, dim, name); \
  __define_mat_add_impl(T, dim, name); \
  __define_mat_sub_impl(T, dim, name); \
  __define_mat_mul_impl(T, dim, name); \
  __define_mat_div_impl(T, dim, name);

#pragma endregion MatrixMacros

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

__define_mat_all(float, 4, mat4);

#pragma endregion MacrosThatIWroteLikeanInsanePerson

typedef vec4 quat; 
quat  quat_identity();
float quat_normal(quat q);
quat  quat_normalize(quat q);
quat  quat_conjugate(quat q);
quat  quat_inverse(quat q);
quat  quat_mul(quat q0, quat q1);
float quat_dot(quat q0, quat q1);
vec3 vec3_cross(vec3 vector_0, vec3 vector_1);
vec3 vec3_rotate(vec3 v, quat q);
mat4 mat4_identity();
mat4 quat_to_mat4(quat q);
mat4 quat_to_rotation_matrix(quat q, vec3 center);
quat quat_from_axis_angle(vec3 axis, float angle, bool normalize);
quat quat_slerp(quat q_0, quat q_1, float percentage);
double range_convert_double(double value, double old_min, double old_max, double new_min, double new_max);
void rgbu_to_uint32_t(uint32_t r, uint32_t g, uint32_t b, uint32_t *out_uint32_t);
void uint32_t_to_rgb(uint32_t rgbu, uint32_t *out_r, uint32_t *out_g, uint32_t *out_b);
void rgb_uint32_t_to_vec3(uint32_t r, uint32_t g, uint32_t b, vec3 *out_v);
void vec3_to_rgb_uint32_t(vec3 v, uint32_t *out_r, uint32_t *out_g, uint32_t *out_b);