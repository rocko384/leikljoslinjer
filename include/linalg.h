#pragma once

#define Real float
#define EPSILON ((Real)1e-6)

typedef struct {
	Real x;
	Real y;
} vec2;

typedef struct {
	Real x;
	Real y;
	Real z;
} vec3;

typedef struct {
	Real x;
	Real y;
	Real z;
	Real w;
} vec4;

typedef struct {
	vec2 row0;
	vec2 row1;
} mat2;

typedef struct {
	vec3 row0;
	vec3 row1;
	vec3 row2;
} mat3;

typedef struct {
	vec4 row0;
	vec4 row1;
	vec4 row2;
	vec4 row3;
} mat4;

vec2 add_vec2(vec2 a, vec2 b);
vec3 add_vec3(vec3 a, vec3 b);
vec4 add_vec4(vec4 a, vec4 b);

vec2 sub_vec2(vec2 a, vec2 b);
vec3 sub_vec3(vec3 a, vec3 b);
vec4 sub_vec4(vec4 a, vec4 b);

vec2 scale_vec2_scalar(vec2 a, Real s);
vec3 scale_vec3_scalar(vec3 a, Real s);
vec4 scale_vec4_scalar(vec4 a, Real s);

vec2 scale_vec2_vec2(vec2 a, vec2 b);
vec3 scale_vec3_vec3(vec3 a, vec3 b);
vec4 scale_vec4_vec4(vec4 a, vec4 b);

Real dot_vec2(vec2 a, vec2 b);
Real dot_vec3(vec3 a, vec3 b);
Real dot_vec4(vec4 a, vec4 b);

Real mag_vec2(vec2 a);
Real mag_vec3(vec3 a);
Real mag_vec4(vec4 a);

Real mag2_vec2(vec2 a);
Real mag2_vec3(vec3 a);
Real mag2_vec4(vec4 a);

vec2 normalize_vec2(vec2 a);
vec3 normalize_vec3(vec3 a);
vec4 normalize_vec4(vec4 a);

vec3 cross_vec3(vec3 a, vec3 b);

mat2 ident_mat2();
mat3 ident_mat3();
mat4 ident_mat4();

mat2 add_mat2(mat2 a, mat2 b);
mat3 add_mat3(mat3 a, mat3 b);
mat4 add_mat4(mat4 a, mat4 b);

mat2 sub_mat2(mat2 a, mat2 b);
mat3 sub_mat3(mat3 a, mat3 b);
mat4 sub_mat4(mat4 a, mat4 b);

mat2 scale_mat2_scalar(mat2 a, Real s);
mat3 scale_mat3_scalar(mat3 a, Real s);
mat4 scale_mat4_scalar(mat4 a, Real s);

mat2 mul_mat2(mat2 a, mat2 b);
mat3 mul_mat3(mat3 a, mat3 b);
mat4 mul_mat4(mat4 a, mat4 b);

vec2 mul_mat2_vec2(mat2 a, vec2 b);
vec3 mul_mat3_vec3(mat3 a, vec3 b);
vec4 mul_mat4_vec4(mat4 a, vec4 b);

Real clamp(Real a, Real min, Real max);