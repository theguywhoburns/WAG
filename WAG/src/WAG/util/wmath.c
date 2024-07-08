#include <math.h>
#include <WAG/util/wmath.h>


double wsin(double x) {
	return sin(x);
}

double wcos(double x) {
	return cos(x);
}

double wtan(double x) {
	return tan(x);
}

double wctg(double x) {
	return 1.0f / tan(x);
}

double wacos(double x) {
	return acos(x);
}

double wasin(double x) {
	return asin(x);
}

double watan(double x) {
	return atan(x);
}

double wactg(double x) {
	return 1.0f / atan(x);
}


double wsqrt(double x) {
	return sqrt(x);
}

double wabs(double x) {
	return fabs(x);
}

double wfloor(double x) {
	return floor(x);
}

double wceil(double x) {
	return ceil(x);
}

double wlog2(double x) {
	return log2(x);
}

double wpow(double x, double y) {
	return pow(x, y);
}


//TODO:
int32_t wrandom() {
 return 0;
}

//TODO:
double wfrandom() {
	return 0.0f;
}

//TODO:
double wfrandom_range(double min, double max) {
	return min - max;
}


__define_vec2_all_impl(vec2, float, vec2);
__define_vec2_all_impl(vec2d, double, vec2d);
__define_vec2_all_impl(vec2u, uint32_t, vec2u);
__define_vec2_all_impl(vec2i, int32_t, vec2i);

__define_vec3_all_impl(vec3, float, vec3);
__define_vec3_all_impl(vec3d, double, vec3d);
__define_vec3_all_impl(vec3u, uint32_t, vec3u);
__define_vec3_all_impl(vec3i, int32_t, vec3i);

__define_vec4_all_impl(vec4, float, vec4);
__define_vec4_all_impl(vec4d, double, vec4d);
__define_vec4_all_impl(vec4u, uint32_t, vec4u);
__define_vec4_all_impl(vec4i, int32_t, vec4i);

__define_mat_all_impl(float, 4, mat4);

quat  quat_identity() { return (quat){0.0f, 0.0f, 0.0f, 1.0f}; }
float quat_normal(quat q) { return sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w); }
quat  quat_normalize(quat q) { float _q = quat_normal(q); return (quat){q.x / _q, q.y / _q, q.z / _q, q.w / _q}; }
quat  quat_conjugate(quat q) { return (quat){-q.x, -q.y, -q.z, q.w}; }
quat  quat_inverse(quat q) {return quat_normalize(quat_conjugate(q)); }
quat  quat_mul(quat q0, quat q1) {
	return (quat){q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y,
		q0.w * q1.y + q0.y * q1.w + q0.z * q1.x - q0.x * q1.z,
		q0.w * q1.z + q0.z * q1.w + q0.x * q1.y - q0.y * q1.x,
		q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z};
}

float quat_dot(quat q0, quat q1) {
	return q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
}

vec3 vec3_cross(vec3 vector_0, vec3 vector_1) {
  return (vec3){
    vector_0.y * vector_1.z - vector_0.z * vector_1.y,
    vector_0.z * vector_1.x - vector_0.x * vector_1.z,
    vector_0.x * vector_1.y - vector_0.y * vector_1.x
	};
}

vec3 vec3_rotate(vec3 v, quat q) {
	vec3 u = vec3_create(q.x, q.y, q.z);
	float s = q.w;

	return vec3_add(
		vec3_add(
			vec3_mul_scalar(u, 2.0f * vec3_dot(u, v)),
			vec3_mul_scalar(v, (s * s - vec3_dot(u, u)))),
		vec3_mul_scalar(vec3_cross(u, v), 2.0f * s));
}

mat4 quat_to_mat4(quat q) {
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

mat4 quat_to_rotation_matrix(quat q, vec3 center) {
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

quat quat_slerp(quat q_0, quat q_1, float percentage) {
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


double range_convert_double(double value, double old_min, double old_max, double new_min, double new_max) {
	return (((value - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min;
}

void rgbu_to_uint32_t(uint32_t r, uint32_t g, uint32_t b, uint32_t *out_uint32_t) {
  *out_uint32_t = (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}


void uint32_t_to_rgb(uint32_t rgbu, uint32_t *out_r, uint32_t *out_g, uint32_t *out_b) {
  *out_r = (rgbu >> 16) & 0xFF;
  *out_g = (rgbu >> 8) & 0xFF;
  *out_b = (rgbu)&0xFF;
}

void rgb_uint32_t_to_vec3(uint32_t r, uint32_t g, uint32_t b, vec3 *out_v) {
  out_v->r = r / 255.0f;
  out_v->g = g / 255.0f;
  out_v->b = b / 255.0f;
}

void vec3_to_rgb_uint32_t(vec3 v, uint32_t *out_r, uint32_t *out_g, uint32_t *out_b) {
  *out_r = (uint32_t)v.r * 255;
  *out_g = (uint32_t)v.g * 255;
  *out_b = (uint32_t)v.b * 255;
}


