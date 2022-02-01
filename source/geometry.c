#include "geometry.h"

#include <math.h>

vec3 reflect(vec3 a, vec3 n) {
	Real _2dot = 2 * dot_vec3(a, n);

	return sub_vec3(a, scale_vec3_scalar(n, _2dot));
}


intersect_result ray_intersect_sphere(ray* r, sphere* s) {
	vec3 dir = normalize_vec3(r->direction);
	vec3 o_c = sub_vec3(r->origin, s->position);
	Real mag2_o_c = mag2_vec3(o_c);
	Real diverg = (dot_vec3(dir, o_c) * dot_vec3(dir, o_c)) - (mag2_o_c - (s->radius * s->radius));

	if (diverg < 0) {
		return (intersect_result) { { 0, 0, 0 }, 0, false };
	}

	Real dl = -1 * dot_vec3(dir, o_c);

	if (dl < 0) {
		return (intersect_result) { { 0, 0, 0 }, 0, false };
	}

	Real d1 = dl + sqrt(diverg);
	Real d2 = dl - sqrt(diverg);

	if (d1 < d2) {
		return (intersect_result) { add_vec3(r->origin, scale_vec3_scalar(dir, d1)), d1, true };
	}

	return (intersect_result) { add_vec3(r->origin, scale_vec3_scalar(dir, d2)), d2, true };
}