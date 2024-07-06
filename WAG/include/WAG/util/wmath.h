#pragma once

#include <defines.h>

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

INLINE bool wispow2(uint64_t val) { return (val != 0) && ((val & (val - 1)) == 0); }
INLINE double wsign(double x) { return x == 0.0f ? 0.0f : x < 0.0f ? -1.0f : 1.0f; }
INLINE bool wfloat_cmp(float a, float b) { return (float)wabs(a - b) < FLOAT_EPSILON; }
INLINE bool wdouble_cmp(double a, double b) { return wabs(a - b) < FLOAT_EPSILON; }

// For vector comparisons
INLINE bool __float_compare(float a, float b) { return wfloat_cmp(a, b); }
INLINE bool __double_compare(double a, double b) { return wdouble_cmp(a, b); }
INLINE bool __uint32_t_compare(int64_t a, int64_t b) { return a == b; }
INLINE bool __int32_t_compare(int64_t a, int64_t b) { return a == b; }

// TODO: Stop writing code while on crack

#pragma region MacrosThatIWroteLikeanInsanePerson
#pragma region VectorMacros
#define __define_vec2(T, name) typedef union _##T##name { struct { T x, y; }; struct { T s, t; }; struct { T r, g; }; struct { T u, v; }; T data[2]; } name
#define __define_vec3(T, name) typedef union _##T##name { struct { T x, y, z; }; struct { T s, t, p; }; struct { T r, g, b; }; struct { T u, v, w; }; T data[3]; } name
#define __define_vec4(T, name) typedef union _##T##name { struct { T x, y, z, w; }; struct { T s, t, p, q; }; struct { T r, g, b, a; }; T data[4]; } name

#define __define_vec2_create(TRET, T, name) INLINE TRET name##_create(T x, T y) { TRET result; result.x = x; result.y = y; return result; }
#define __define_vec3_create(TRET, T, name) INLINE TRET name##_create(T x, T y, T z) { TRET result; result.x = x; result.y = y; result.z = z; return result; }
#define __define_vec4_create(TRET, T, name) INLINE TRET name##_create(T x, T y, T z, T w) { TRET result; result.x = x; result.y = y; result.z = z; result.w = w; return result; }

#define __define_vec2_zero(TRET, T, name) INLINE TRET name##_zero() { return (TRET){(T)0.0f, (T)0.0f}; }
#define __define_vec3_zero(TRET, T, name) INLINE TRET name##_zero() { return (TRET){(T)0.0f, (T)0.0f, (T)0.0f}; }
#define __define_vec4_zero(TRET, T, name) INLINE TRET name##_zero() { return (TRET){(T)0.0f, (T)0.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_one(TRET, T, name) INLINE TRET name##_one() { return (TRET){(T)1.0f, (T)1.0f}; }
#define __define_vec3_one(TRET, T, name) INLINE TRET name##_one() { return (TRET){(T)1.0f, (T)1.0f, (T)1.0f}; }
#define __define_vec4_one(TRET, T, name) INLINE TRET name##_one() { return (TRET){(T)1.0f, (T)1.0f, (T)1.0f, (T)1.0f}; }

#define __define_vec2_up(TRET, T, name) INLINE TRET name##_up() { return (TRET){(T)0.0f, (T)1.0f}; }
#define __define_vec3_up(TRET, T, name) INLINE TRET name##_up() { return (TRET){(T)0.0f, (T)1.0f, (T)0.0f}; }
#define __define_vec4_up(TRET, T, name) INLINE TRET name##_up() { return (TRET){(T)0.0f, (T)1.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_down(TRET, T, name) INLINE TRET name##_down() { return (TRET){(T)0.0f, (T)-1.0f}; }
#define __define_vec3_down(TRET, T, name) INLINE TRET name##_down() { return (TRET){(T)0.0f, (T)-1.0f, (T)0.0f}; }
#define __define_vec4_down(TRET, T, name) INLINE TRET name##_down() { return (TRET){(T)0.0f, (T)-1.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_left(TRET, T, name) INLINE TRET name##_left() { return (TRET){(T)-1.0f, (T)0.0f}; }
#define __define_vec3_left(TRET, T, name) INLINE TRET name##_left() { return (TRET){(T)-1.0f, (T)0.0f, (T)0.0f}; }
#define __define_vec4_left(TRET, T, name) INLINE TRET name##_left() { return (TRET){(T)-1.0f, (T)0.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_right(TRET, T, name) INLINE TRET name##_right() { return (TRET){(T)1.0f, (T)0.0f}; }
#define __define_vec3_right(TRET, T, name) INLINE TRET name##_right() { return (TRET){(T)1.0f, (T)0.0f, (T)0.0f}; }
#define __define_vec4_right(TRET, T, name) INLINE TRET name##_right() { return (TRET){(T)1.0f, (T)0.0f, (T)0.0f, (T)0.0f}; }

#define __define_vec2_add(TRET, name) INLINE TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; return result; }
#define __define_vec3_add(TRET, name) INLINE TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; result.z = a.z + b.z; return result; }
#define __define_vec4_add(TRET, name) INLINE TRET name##_add(TRET a, TRET b) { TRET result; result.x = a.x + b.x; result.y = a.y + b.y; result.z = a.z + b.z; result.w = a.w + b.w; return result; }

#define __define_vec2_sub(TRET, name) INLINE TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; return result; }
#define __define_vec3_sub(TRET, name) INLINE TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; result.z = a.z - b.z; return result; }
#define __define_vec4_sub(TRET, name) INLINE TRET name##_sub(TRET a, TRET b) { TRET result; result.x = a.x - b.x; result.y = a.y - b.y; result.z = a.z - b.z; result.w = a.w - b.w; return result; }

#define __define_vec2_mul(TRET, name) INLINE TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; return result; }
#define __define_vec3_mul(TRET, name) INLINE TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; result.z = a.z * b.z; return result; }
#define __define_vec4_mul(TRET, name) INLINE TRET name##_mul(TRET a, TRET b) { TRET result; result.x = a.x * b.x; result.y = a.y * b.y; result.z = a.z * b.z; result.w = a.w * b.w; return result; }

#define __define_vec2_mul_scalar(TRET, T, name) INLINE TRET name##_mul_scalar(TRET a, T b) { TRET result; result.x = a.x * b; result.y = a.y * b; return result; }
#define __define_vec3_mul_scalar(TRET, T, name) INLINE TRET name##_mul_scalar(TRET a, T b) { TRET result; result.x = a.x * b; result.y = a.y * b; result.z = a.z * b; return result; }
#define __define_vec4_mul_scalar(TRET, T, name) INLINE TRET name##_mul_scalar(TRET a, T b) { TRET result; result.x = a.x * b; result.y = a.y * b; result.z = a.z * b; result.w = a.w * b; return result; }

#define __define_vec2_mul_add(TRET, name) INLINE TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; return result; }
#define __define_vec3_mul_add(TRET, name) INLINE TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; result.z = a.z * b.z + c.z; return result; }
#define __define_vec4_mul_add(TRET, name) INLINE TRET name##_mul_add(TRET a, TRET b, TRET c) { TRET result; result.x = a.x * b.x + c.x; result.y = a.y * b.y + c.y; result.z = a.z * b.z + c.z; result.w = a.w * b.w + c.w; return result; }
 
#define __define_vec2_div(TRET, name) INLINE TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; return result; }
#define __define_vec3_div(TRET, name) INLINE TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; result.z = a.z / b.z; return result; }
#define __define_vec4_div(TRET, name) INLINE TRET name##_div(TRET a, TRET b) { TRET result; result.x = a.x / b.x; result.y = a.y / b.y; result.z = a.z / b.z; result.w = a.w / b.w; return result; }

#define __define_vec2_length_sq(T, TRET, name) INLINE TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y; }
#define __define_vec3_length_sq(T, TRET, name) INLINE TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
#define __define_vec4_length_sq(T, TRET, name) INLINE TRET name##_length_sq(T a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }

#define __define_vec2_length(T, TRET, name) INLINE TRET name##_length(T a) { return (TRET)wsqrt(a.x * a.x + a.y * a.y); }
#define __define_vec3_length(T, TRET, name) INLINE TRET name##_length(T a) { return (TRET)wsqrt(a.x * a.x + a.y * a.y + a.z * a.z); }
#define __define_vec4_length(T, TRET, name) INLINE TRET name##_length(T a) { return (TRET)wsqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w); }

#define __define_vec2_normalize(TRET, T, name) void name##_normalize(TRET* a) { const T len = name##_length(*a); a->x /= len; a->y /= len; }
#define __define_vec3_normalize(TRET, T, name) void name##_normalize(TRET* a) { const T len = name##_length(*a); a->x /= len; a->y /= len; a->z /= len; }
#define __define_vec4_normalize(TRET, T, name) void name##_normalize(TRET* a) { const T len = name##_length(*a); a->x /= len; a->y /= len; a->z /= len; a->w /= len; }

#define __define_vec2_normalized(TRET, T, name) INLINE TRET name##_normalized(TRET a) { name##_normalize(&a); return a; }
#define __define_vec3_normalized(TRET, T, name) INLINE TRET name##_normalized(TRET a) { name##_normalize(&a); return a; }
#define __define_vec4_normalized(TRET, T, name) INLINE TRET name##_normalized(TRET a) { name##_normalize(&a); return a; }

#define __define_vec2_dot(TRET, T, name) INLINE T name##_dot(TRET a, TRET b) { return a.x * b.x + a.y * b.y; }
#define __define_vec3_dot(TRET, T, name) INLINE T name##_dot(TRET a, TRET b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
#define __define_vec4_dot(TRET, T, name) INLINE T name##_dot(TRET a, TRET b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

#define __define_vec2_compare(TRET, T, name) INLINE bool name##_compare(TRET a, TRET b) { return __##T##_compare(a.x, b.x) && __##T##_compare(a.y, b.y); }
#define __define_vec3_compare(TRET, T, name) INLINE bool name##_compare(TRET a, TRET b) { return __##T##_compare(a.x, b.x) && __##T##_compare(a.y, b.y) && __##T##_compare(a.z, b.z); }
#define __define_vec4_compare(TRET, T, name) INLINE bool name##_compare(TRET a, TRET b) { return __##T##_compare(a.x, b.x) && __##T##_compare(a.y, b.y) && __##T##_compare(a.z, b.z) && __##T##_compare(a.w, b.w); }

#define __define_vec2_min(TRET, T, name) INLINE TRET name##_min(TRET a, TRET b) { return name##_create(WMIN(a.x, b.x), WMIN(a.y, b.y)); }
#define __define_vec3_min(TRET, T, name) INLINE TRET name##_min(TRET a, TRET b) { return name##_create(WMIN(a.x, b.x), WMIN(a.y, b.y), WMIN(a.z, b.z)); }
#define __define_vec4_min(TRET, T, name) INLINE TRET name##_min(TRET a, TRET b) { return name##_create(WMIN(a.x, b.x), WMIN(a.y, b.y), WMIN(a.z, b.z), WMIN(a.w, b.w)); }

#define __define_vec2_max(TRET, T, name) INLINE TRET name##_max(TRET a, TRET b) { return name##_create(WMAX(a.x, b.x), WMAX(a.y, b.y)); }
#define __define_vec3_max(TRET, T, name) INLINE TRET name##_max(TRET a, TRET b) { return name##_create(WMAX(a.x, b.x), WMAX(a.y, b.y), WMAX(a.z, b.z)); }
#define __define_vec4_max(TRET, T, name) INLINE TRET name##_max(TRET a, TRET b) { return name##_create(WMAX(a.x, b.x), WMAX(a.y, b.y), WMAX(a.z, b.z), WMAX(a.w, b.w)); }

#define __define_vec2_sign(TRET, T, name) INLINE TRET name##_sign(TRET a) { return name##_create((T)sign((double)a.x), (T)sign((double)a.y)); }
#define __define_vec3_sign(TRET, T, name) INLINE TRET name##_sign(TRET a) { return name##_create((T)sign((double)a.x), (T)sign((double)a.y), (T)sign((double)a.z)); }
#define __define_vec4_sign(TRET, T, name) INLINE TRET name##_sign(TRET a) { return name##_create((T)sign((double)a.x), (T)sign((double)a.y), (T)sign((double)a.z), (T)sign((double)a.w)); }

#define __define_vec2_all(TRET, T, name) __define_vec2(T, name); __define_vec2_create(TRET, T, name); __define_vec2_zero(TRET, T, name); __define_vec2_one(TRET, T, name); __define_vec2_up(TRET, T, name); __define_vec2_down(TRET, T, name); __define_vec2_left(TRET, T, name); __define_vec2_right(TRET, T, name); __define_vec2_add(TRET, name); __define_vec2_sub(TRET, name); __define_vec2_mul(TRET, name); __define_vec2_mul_scalar(TRET, T, name); __define_vec2_mul_add(TRET, name); __define_vec2_div(TRET, name); __define_vec2_length_sq(TRET, T, name); __define_vec2_length(TRET, T, name); __define_vec2_normalize(TRET, T, name); __define_vec2_normalized(TRET, T, name); __define_vec2_dot(TRET, T, name); __define_vec2_compare(TRET, T, name); __define_vec2_min(TRET, T, name); __define_vec2_max(TRET, T, name);
#define __define_vec3_all(TRET, T, name) __define_vec3(T, name); __define_vec3_create(TRET, T, name); __define_vec3_zero(TRET, T, name); __define_vec3_one(TRET, T, name); __define_vec3_up(TRET, T, name); __define_vec3_down(TRET, T, name); __define_vec3_left(TRET, T, name); __define_vec3_right(TRET, T, name); __define_vec3_add(TRET, name); __define_vec3_sub(TRET, name); __define_vec3_mul(TRET, name); __define_vec3_mul_scalar(TRET, T, name); __define_vec3_mul_add(TRET, name); __define_vec3_div(TRET, name); __define_vec3_length_sq(TRET, T, name); __define_vec3_length(TRET, T, name); __define_vec3_normalize(TRET, T, name); __define_vec3_normalized(TRET, T, name); __define_vec3_dot(TRET, T, name); __define_vec3_compare(TRET, T, name); __define_vec3_min(TRET, T, name); __define_vec3_max(TRET, T, name);
#define __define_vec4_all(TRET, T, name) __define_vec4(T, name); __define_vec4_create(TRET, T, name); __define_vec4_zero(TRET, T, name); __define_vec4_one(TRET, T, name); __define_vec4_up(TRET, T, name); __define_vec4_down(TRET, T, name); __define_vec4_left(TRET, T, name); __define_vec4_right(TRET, T, name); __define_vec4_add(TRET, name); __define_vec4_sub(TRET, name); __define_vec4_mul(TRET, name); __define_vec4_mul_scalar(TRET, T, name); __define_vec4_mul_add(TRET, name); __define_vec4_div(TRET, name); __define_vec4_length_sq(TRET, T, name); __define_vec4_length(TRET, T, name); __define_vec4_normalize(TRET, T, name); __define_vec4_normalized(TRET, T, name); __define_vec4_dot(TRET, T, name); __define_vec4_compare(TRET, T, name); __define_vec4_min(TRET, T, name); __define_vec4_max(TRET, T, name);
#pragma endregion VectorMacros

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

#pragma endregion MacrosThatIWroteLikeanInsanePerson

typedef union _mat4_u {
	float data[16];
} mat4;

typedef vec4 quat; 
INLINE quat  quat_identity() { return (quat){0.0f, 0.0f, 0.0f, 1.0f}; }
INLINE float quat_normal(quat q) { return sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w); }
INLINE quat  quat_normalize(quat q) { float _q = quat_normal(q); return (quat){q.x / _q, q.y / _q, q.z / _q, q.w / _q}; }
INLINE quat  quat_conjugate(quat q) { return (quat){-q.x, -q.y, -q.z, q.w}; }
INLINE quat  quat_inverse(quat q) {return quat_normalize(quat_conjugate(q)); }
INLINE quat  quat_mul(quat q0, quat q1) {
	return (quat){q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y,
		q0.w * q1.y + q0.y * q1.w + q0.z * q1.x - q0.x * q1.z,
		q0.w * q1.z + q0.z * q1.w + q0.x * q1.y - q0.y * q1.x,
		q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z};
}

INLINE float quat_dot(quat q0, quat q1) {
	return q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
}

INLINE vec3 vec3_cross(vec3 vector_0, vec3 vector_1) {
  return (vec3){
    vector_0.y * vector_1.z - vector_0.z * vector_1.y,
    vector_0.z * vector_1.x - vector_0.x * vector_1.z,
    vector_0.x * vector_1.y - vector_0.y * vector_1.x
	};
}

INLINE vec3 vec3_rotate(vec3 v, quat q) {
	vec3 u = vec3_create(q.x, q.y, q.z);
	float s = q.w;

	return vec3_add(
		vec3_add(
			vec3_mul_scalar(u, 2.0f * vec3_dot(u, v)),
			vec3_mul_scalar(v, (s * s - vec3_dot(u, u)))),
		vec3_mul_scalar(vec3_cross(u, v), 2.0f * s));
}

INLINE mat4 mat4_identity() {
	mat4 out;
	out.data[0] = 1.0f;
	out.data[5] = 1.0f;
	out.data[10] = 1.0f;
	out.data[15] = 1.0f;
	return out;
}

INLINE mat4 quat_to_mat4(quat q) {
	mat4 out_matrix = mat4_identity();

	float x = q.x, y = q.y, z = q.z, w = q.w;
	float x2 = x + x, y2 = y + y, z2 = z + z;
	float xx = x * x2, xy = x * y2, xz = x * z2;
	float yy = y * y2, yz = y * z2, zz = z * z2;
	float wx = w * x2, wy = w * y2, wz = w * z2;

	out_matrix.data[0] = 1.0f - (yy + zz);
	out_matrix.data[1] = xy - wz;
	out_matrix.data[2] = xz + wy;

	out_matrix.data[4] = xy + wz;
	out_matrix.data[5] = 1.0f - (xx + zz);
	out_matrix.data[6] = yz - wx;

	out_matrix.data[8] = xz - wy;
	out_matrix.data[9] = yz + wx;
	out_matrix.data[10] = 1.0f - (xx + yy);

	return out_matrix;
}

INLINE mat4 quat_to_rotation_matrix(quat q, vec3 center) {
  mat4 out_matrix;
  float *o = out_matrix.data;
  const float x2 = q.x + q.x;
  const float y2 = q.y + q.y;
  const float z2 = q.z + q.z;
  const float xx = q.x * x2;
  const float xy = q.x * y2;
  const float xz = q.x * z2;
  const float yy = q.y * y2;
  const float yz = q.y * z2;
  const float zz = q.z * z2;
  const float wx = q.w * x2;
  const float wy = q.w * y2;
  const float wz = q.w * z2;
  o[0] = 1.0f - (yy + zz);
  o[1] = xy - wz;
  o[2] = xz + wy;
  o[3] = center.x - center.x * o[0] - center.y * o[1] - center.z * o[2];
  o[4] = xy + wz;
  o[5] = 1.0f - (xx + zz);
  o[6] = yz - wx;
  o[7] = center.y - center.x * o[4] - center.y * o[5] - center.z * o[6];
  o[8] = xz - wy;
  o[9] = yz + wx;
  o[10] = 1.0f - (xx + yy);
  o[11] = center.z - center.x * o[8] - center.y * o[9] - center.z * o[10];
  o[12] = 0.0f;
  o[13] = 0.0f;
  o[14] = 0.0f;
  o[15] = 1.0f;
  return out_matrix;
}

quat quat_from_axis_angle(vec3 axis, float angle, bool normalize) {
  const float half_angle = 0.5f * angle;
  float s = (float)wsin(half_angle);
  float c = (float)wcos(half_angle);
  quat q = (quat){s * axis.x, s * axis.y, s * axis.z, c};
  return normalize ? quat_normalize(q) : q;
}

INLINE quat quat_slerp(quat q_0, quat q_1, float percentage) {
  quat out_quaternion;

  // Source: https://en.wikipedia.org/wiki/Slerp
  // Only unit quaternions are valid rotations.
  // Normalize to avoid undefined behavior.
  quat v0 = quat_normalize(q_0);
  quat v1 = quat_normalize(q_1);

  // Compute the cosine of the angle between the two vectors.
  float dot = quat_dot(v0, v1);

  // If the dot product is negative, slerp won't take
  // the shorter path. Note that v1 and -v1 are equivalent when
  // the negation is applied to all four components. Fix by
  // reversing one quaternion.
  if (dot < 0.0f) {
    v1.x = -v1.x;
    v1.y = -v1.y;
    v1.z = -v1.z;
    v1.w = -v1.w;
    dot = -dot;
  }

  const float DOT_THRESHOLD = 0.9995f;
  if (dot > DOT_THRESHOLD) {
    // If the inputs are too close for comfort, linearly interpolate
    // and normalize the result.
    out_quaternion = (quat){
      v0.x + ((v1.x - v0.x) * percentage),
      v0.y + ((v1.y - v0.y) * percentage),
      v0.z + ((v1.z - v0.z) * percentage),
      v0.w + ((v1.w - v0.w) * percentage)
    };
    return quat_normalize(out_quaternion);
  }

  // Since dot is in range [0, DOT_THRESHOLD], acos is safe
  float theta_0 = (float)wacos(dot);
  // theta_0 = angle between input vectors
  float theta = theta_0 * percentage;
  // theta = angle between v0 and result
  float sin_theta = (float)wsin(theta);
  // compute this value only once
  float sin_theta_0 = (float)wsin(theta_0);
  // compute this value only once
  float s0 = (float)wcos(theta) - dot * sin_theta / sin_theta_0;
  // == sin(theta_0 - theta) / sin(theta_0)
  float s1 = sin_theta / sin_theta_0;
  return (quat){
    (v0.x * s0) + (v1.x * s1),
    (v0.y * s0) + (v1.y * s1),
    (v0.z * s0) + (v1.z * s1),
    (v0.w * s0) + (v1.w * s1)
  };
}


INLINE double range_convert_double(double value, double old_min, double old_max, double new_min, double new_max) {
	return (((value - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min;
}

INLINE void rgbu_to_uint32_t(uint32_t r, uint32_t g, uint32_t b, uint32_t *out_uint32_t) {
  *out_uint32_t = (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}


INLINE void uint32_t_to_rgb(uint32_t rgbu, uint32_t *out_r, uint32_t *out_g, uint32_t *out_b) {
  *out_r = (rgbu >> 16) & 0xFF;
  *out_g = (rgbu >> 8) & 0xFF;
  *out_b = (rgbu)&0xFF;
}

INLINE void rgb_uint32_t_to_vec3(uint32_t r, uint32_t g, uint32_t b, vec3 *out_v) {
  out_v->r = r / 255.0f;
  out_v->g = g / 255.0f;
  out_v->b = b / 255.0f;
}

INLINE void vec3_to_rgb_uint32_t(vec3 v, uint32_t *out_r, uint32_t *out_g, uint32_t *out_b) {
  *out_r = (uint32_t)v.r * 255;
  *out_g = (uint32_t)v.g * 255;
  *out_b = (uint32_t)v.b * 255;
}

