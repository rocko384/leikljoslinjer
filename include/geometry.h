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
} box;

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
