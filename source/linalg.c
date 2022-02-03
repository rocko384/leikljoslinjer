#include "linalg.h"

#include <math.h>

vec2 add_vec2(vec2 a, vec2 b) {
	return (vec2) { a.x + b.x, a.y + b.y };
}

vec3 add_vec3(vec3 a, vec3 b) {
	return (vec3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

vec4 add_vec4(vec4 a, vec4 b) {
	return (vec4) { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}


vec2 sub_vec2(vec2 a, vec2 b) {
	return (vec2) { a.x - b.x, a.y - b.y };
}

vec3 sub_vec3(vec3 a, vec3 b) {
	return (vec3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

vec4 sub_vec4(vec4 a, vec4 b) {
	return (vec4) { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}


vec2 scale_vec2_scalar(vec2 a, Real s) {
	return (vec2) { a.x * s, a.y * s };
}

vec3 scale_vec3_scalar(vec3 a, Real s) {
	return (vec3) { a.x * s, a.y * s, a.z * s };
}

vec4 scale_vec4_scalar(vec4 a, Real s) {
	return (vec4) { a.x * s, a.y * s, a.z * s, a.w * s };
}


vec2 scale_vec2_vec2(vec2 a, vec2 b) {
	return (vec2) { a.x * b.x, a.y * b.y };
}

vec3 scale_vec3_vec3(vec3 a, vec3 b) {
	return (vec3) { a.x * b.x, a.y * b.y, a.z * b.z };
}

vec4 scale_vec4_vec4(vec4 a, vec4 b) {
	return (vec4) { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
}


Real dot_vec2(vec2 a, vec2 b) {
	return (a.x * b.x) + (a.y * b.y);
}

Real dot_vec3(vec3 a, vec3 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Real dot_vec4(vec4 a, vec4 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}


Real mag_vec2(vec2 a) {
	return sqrt((a.x * a.x) + (a.y * a.y));
}

Real mag_vec3(vec3 a) {
	return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

Real mag_vec4(vec4 a) {
	return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w * a.w));
}


Real mag2_vec2(vec2 a) {
	return (a.x * a.x) + (a.y * a.y);
}

Real mag2_vec3(vec3 a) {
	return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}

Real mag2_vec4(vec4 a) {
	return (a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w * a.w);
}


vec2 normalize_vec2(vec2 a) {
	return scale_vec2_scalar(a, 1 / mag_vec2(a));
}

vec3 normalize_vec3(vec3 a) {
	return scale_vec3_scalar(a, 1 / mag_vec3(a));
}

vec4 normalize_vec4(vec4 a) {
	return scale_vec4_scalar(a, 1 / mag_vec4(a));
}


vec3 cross_vec3(vec3 a, vec3 b) {
	Real x = ((a.y * b.z) - (a.z * b.y));
	Real y = ((a.z * b.x) - (a.x * b.z));
	Real z = ((a.x * b.y) - (a.y * b.x));
	vec3 ret = { x, y, z };
	return ret;
}


mat2 ident_mat2() {
	return (mat2) {
		{ 1, 0 },
		{ 0, 1 }
	};
}

mat3 ident_mat3() {
	return (mat3) {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	};
}

mat4 ident_mat4() {
	return (mat4) {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};
}


mat2 add_mat2(mat2 a, mat2 b) {
	return (mat2) { add_vec2(a.row0, b.row0), add_vec2(a.row1, b.row1) };
}

mat3 add_mat3(mat3 a, mat3 b) {
	return (mat3) { add_vec3(a.row0, b.row0), add_vec3(a.row1, b.row1), add_vec3(a.row2, b.row2) };
}

mat4 add_mat4(mat4 a, mat4 b) {
	return (mat4) { add_vec4(a.row0, b.row0), add_vec4(a.row1, b.row1), add_vec4(a.row2, b.row2), add_vec4(a.row3, b.row3) };
}


mat2 sub_mat2(mat2 a, mat2 b) {
	return (mat2) { sub_vec2(a.row0, b.row0), sub_vec2(a.row1, b.row1) };
}

mat3 sub_mat3(mat3 a, mat3 b) {
	return (mat3) { sub_vec3(a.row0, b.row0), sub_vec3(a.row1, b.row1), sub_vec3(a.row2, b.row2) };
}

mat4 sub_mat4(mat4 a, mat4 b) {
	return (mat4) { sub_vec4(a.row0, b.row0), sub_vec4(a.row1, b.row1), sub_vec4(a.row2, b.row2), sub_vec4(a.row3, b.row3) };
}


mat2 scale_mat2_scalar(mat2 a, Real s) {
	return (mat2) { scale_vec2_scalar(a.row0, s), scale_vec2_scalar(a.row1, s) };
}

mat3 scale_mat3_scalar(mat3 a, Real s) {
	return (mat3) { scale_vec3_scalar(a.row0, s), scale_vec3_scalar(a.row1, s), scale_vec3_scalar(a.row2, s) };
}

mat4 scale_mat4_scalar(mat4 a, Real s) {
	return (mat4) { scale_vec4_scalar(a.row0, s), scale_vec4_scalar(a.row1, s), scale_vec4_scalar(a.row2, s), scale_vec4_scalar(a.row3, s) };
}


mat2 mul_mat2(mat2 a, mat2 b) {
	vec2 bcol0 = { b.row0.x, b.row1.x };
	vec2 bcol1 = { b.row0.y, b.row1.y };

	return (mat2) { dot_vec2(a.row0, bcol0), dot_vec2(a.row1, bcol1) };
}

mat3 mul_mat3(mat3 a, mat3 b) {
	vec3 bcol0 = { b.row0.x, b.row1.x, b.row2.x };
	vec3 bcol1 = { b.row0.y, b.row1.y, b.row2.y };
	vec3 bcol2 = { b.row0.z, b.row1.z, b.row2.z };

	return (mat3) { dot_vec3(a.row0, bcol0), dot_vec3(a.row1, bcol1), dot_vec3(a.row2, bcol2) };
}

mat4 mul_mat4(mat4 a, mat4 b) {
	vec4 bcol0 = { b.row0.x, b.row1.x, b.row2.x, b.row3.x };
	vec4 bcol1 = { b.row0.y, b.row1.y, b.row2.y, b.row3.y };
	vec4 bcol2 = { b.row0.z, b.row1.z, b.row2.z, b.row3.z };
	vec4 bcol3 = { b.row0.w, b.row1.w, b.row2.w, b.row3.w };

	return (mat4) { dot_vec4(a.row0, bcol0), dot_vec4(a.row1, bcol1), dot_vec4(a.row2, bcol2), dot_vec4(a.row3, bcol3) };
}


vec2 mul_mat2_vec2(mat2 a, vec2 b) {
	return (vec2) { dot_vec2(a.row0, b), dot_vec2(a.row1, b) };
}

vec3 mul_mat3_vec3(mat3 a, vec3 b) {
	return (vec3) { dot_vec3(a.row0, b), dot_vec3(a.row1, b), dot_vec3(a.row2, b) };
}

vec4 mul_mat4_vec4(mat4 a, vec4 b) {
	return (vec4) { dot_vec4(a.row0, b), dot_vec4(a.row1, b), dot_vec4(a.row2, b), dot_vec4(a.row3, b) };
}


Real clamp(Real a, Real min, Real max) {
	Real b = fmax(a, min);
	return fmin(b, max);
}


quat ident_quat() {
	return (quat) { 1, 0, 0, 0 };
}

quat mul_quat(quat a, quat b) {
	return (quat) {
		(a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z),
		(a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y),
		(a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x),
		(a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w)
	};
}

quat conjugate_quat(quat q) {
	return (quat) { q.w, -q.x, -q.y, -q.z };
}

Real norm_quat(quat q) {
	return sqrt((q.w * q.w) + (q.x * q.x) + (q.y * q.y) + (q.z * q.z));
}

quat unit_quat(quat q) {
	Real norm = norm_quat(q);
	return (quat) { q.w / norm, q.x / norm, q.y / norm, q.z / norm };
}

quat reciprocal_quat(quat q) {
	Real norm2 = norm_quat(q) * norm_quat(q);
	quat conj = conjugate_quat(q);
	return (quat) { conj.w / norm2, conj.x / norm2, conj.y / norm2, conj.z / norm2 };
}


quat rotate_on_axis(vec3 axis, Real angle) {
	Real a_2 = (angle * PI) / (2 * 180);
	Real sin_a_2 = sin(a_2);
	return (quat) { cos(a_2), sin_a_2 * axis.x, sin_a_2 * axis.y, sin_a_2 * axis.z };
}

vec3 rotate_vec3(vec3 v, quat r) {
	quat point = { 0, v.x, v.y, v.z };
	quat conj = conjugate_quat(r);
	quat res = mul_quat(mul_quat(r, point), conj);

	return (vec3) { res.x, res.y, res.z };
}