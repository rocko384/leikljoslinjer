#pragma once

#include "linalg.h"

#include <stdbool.h>

typedef struct {
	vec3 origin;
	vec3 direction;
} ray;

typedef struct {
	vec3 position;
	Real radius;
} sphere;

typedef struct {
	vec3 min;
	vec3 max;
	vec3 top_normal;
	vec3 front_normal;
} box;

typedef struct {
	vec3 position;
	vec3 top_normal;
	Real height;
	Real radius;
} cylinder;

#define UNIT_SPHERE (sphere) { (vec3) { 0, 0, 0 }, 1 }
#define UNIT_BOX (box) { (vec3) { -0.5, -0.5, -0.5 }, (vec3) { 0.5, 0.5, 0.5 }, (vec3) { 0, 1, 0 }, (vec3) { 0, 0, 1 } }
#define UNIT_CYLINDER (cylinder) { (vec3) { 0, 0, 0 }, (vec3) { 0, 1, 0 }, 2, 1 }

vec3 reflect(vec3 a, vec3 n);

typedef struct {
	vec3 position;
	vec3 normal;
	Real distance;
	bool success;
} intersect_result;

typedef intersect_result(*intersect_func)(ray*, void*);

#define NULL_INTERSECTION (intersect_result) { { 0, 0, 0 }, { 0, 0, 0 }, 0, false }

intersect_result ray_intersect_sphere(ray* r, sphere* s);
intersect_result ray_intersect_box(ray* r, box* b);
intersect_result ray_intersect_cylinder(ray* r, cylinder* c);

void translate_sphere(sphere* s, vec3 v);
void translate_box(box* b, vec3 v);
void translate_cylinder(cylinder* c, vec3 v);

void rotate_box(box* b, quat r);
void rotate_cylinder(cylinder* c, quat r);
