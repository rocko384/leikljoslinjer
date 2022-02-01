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

vec3 reflect(vec3 a, vec3 n);

typedef struct {
	vec3 location;
	Real distance;
	bool success;
} intersect_result;

typedef intersect_result(*intersect_func)(ray*, void*);

intersect_result ray_intersect_sphere(ray* r, sphere* s);