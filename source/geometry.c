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
		return NULL_INTERSECTION;
	}

	Real dl = -1 * dot_vec3(dir, o_c);

	if (dl < 0) {
		return NULL_INTERSECTION;
	}

	Real d1 = dl + sqrt(diverg);
	Real d2 = dl - sqrt(diverg);

	if (d1 < d2) {
		vec3 position = add_vec3(r->origin, scale_vec3_scalar(dir, d1));
		vec3 normal = sub_vec3(position, s->position);
		return (intersect_result) { position, normalize_vec3(normal), d1, true };
	}

	vec3 position = add_vec3(r->origin, scale_vec3_scalar(dir, d2));
	vec3 normal = sub_vec3(position, s->position);
	return (intersect_result) { position, normalize_vec3(normal), d2, true };
}

Real ray_intersect_plane(ray r, vec3 normal, vec3 point) {
	vec3 dir = scale_vec3_scalar(r.direction, 1);
	Real denominator = dot_vec3(dir, normalize_vec3(normal));

	if (denominator > EPSILON) {
		Real d = dot_vec3(sub_vec3(point, r.origin), normalize_vec3(normal)) / denominator;
		return d;
	}

	return -1;
}

Real side_of_plane_point(vec3 p, vec4 plane) {
	return dot_vec4(plane, (vec4) { p.x, p.y, p.z, 1 });
}

intersect_result ray_intersect_box(ray* r, box* b) {
	vec3 dir = normalize_vec3(r->direction);

	vec3 max = {
		fmax(b->min.x, b->max.x),
		fmax(b->min.y, b->max.y),
		fmax(b->min.z, b->max.z)
	};

	vec3 min = {
		fmin(b->min.x, b->max.x),
		fmin(b->min.y, b->max.y),
		fmin(b->min.z, b->max.z)
	};

	vec3 top_normal = normalize_vec3(b->top_normal);
	vec3 bottom_normal = scale_vec3_scalar(top_normal, -1);
	vec3 forward_normal = normalize_vec3(b->front_normal);
	vec3 backward_normal = scale_vec3_scalar(forward_normal, -1);
	vec3 right_normal = normalize_vec3(cross_vec3(top_normal, forward_normal));
	vec3 left_normal = scale_vec3_scalar(right_normal, -1);

	vec4 top_plane = { top_normal.x, top_normal.y, top_normal.z, -dot_vec3(top_normal, max) };
	vec4 bottom_plane = { bottom_normal.x, bottom_normal.y, bottom_normal.z, -dot_vec3(bottom_normal, min) };
	vec4 left_plane = { left_normal.x, left_normal.y, left_normal.z, -dot_vec3(left_normal, min) };
	vec4 right_plane = { right_normal.x, right_normal.y, right_normal.z, -dot_vec3(right_normal, max) };
	vec4 backward_plane = { backward_normal.x, backward_normal.y, backward_normal.z, -dot_vec3(backward_normal, min) };
	vec4 forward_plane = { forward_normal.x, forward_normal.y, forward_normal.z, -dot_vec3(forward_normal, max) };

	Real top_intersection = ray_intersect_plane(*r, bottom_normal, max);
	Real bottom_intersection = ray_intersect_plane(*r, top_normal, min);
	Real left_intersection = ray_intersect_plane(*r, right_normal, min);
	Real right_intersection = ray_intersect_plane(*r, left_normal, max);
	Real backward_intersection = ray_intersect_plane(*r, forward_normal, min);
	Real forward_intersection = ray_intersect_plane(*r, backward_normal, max);

	intersect_result nearest_result = {
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		100000.0,
		false
	};

	if (top_intersection >= 0 && top_intersection < nearest_result.distance) {
		vec3 int_point = add_vec3(r->origin, scale_vec3_scalar(dir, top_intersection));
		Real point_inside_left = side_of_plane_point(int_point, left_plane);
		Real point_inside_right = side_of_plane_point(int_point, right_plane);
		Real point_inside_front = side_of_plane_point(int_point, forward_plane);
		Real point_inside_back = side_of_plane_point(int_point, backward_plane);

		if (point_inside_left < 0 && point_inside_right < 0 && point_inside_front < 0 && point_inside_back < 0) {
			nearest_result.position = int_point;
			nearest_result.normal = top_normal;
			nearest_result.distance = top_intersection;
			nearest_result.success = true;
		}
	}

	if (bottom_intersection >= 0 && bottom_intersection < nearest_result.distance) {
		vec3 int_point = add_vec3(r->origin, scale_vec3_scalar(dir, bottom_intersection));
		Real point_inside_left = side_of_plane_point(int_point, left_plane);
		Real point_inside_right = side_of_plane_point(int_point, right_plane);
		Real point_inside_front = side_of_plane_point(int_point, forward_plane);
		Real point_inside_back = side_of_plane_point(int_point, backward_plane);

		if (point_inside_left < 0 && point_inside_right < 0 && point_inside_front < 0 && point_inside_back < 0) {
			nearest_result.position = int_point;
			nearest_result.normal = bottom_normal;
			nearest_result.distance = bottom_intersection;
			nearest_result.success = true;
		}
	}

	if (left_intersection >= 0 && left_intersection < nearest_result.distance) {
		vec3 int_point = add_vec3(r->origin, scale_vec3_scalar(dir, left_intersection));
		Real point_inside_top = side_of_plane_point(int_point, top_plane);
		Real point_inside_bottom = side_of_plane_point(int_point, bottom_plane);
		Real point_inside_front = side_of_plane_point(int_point, forward_plane);
		Real point_inside_back = side_of_plane_point(int_point, backward_plane);

		if (point_inside_top < 0 && point_inside_bottom < 0 && point_inside_front < 0 && point_inside_back < 0) {
			nearest_result.position = int_point;
			nearest_result.normal = left_normal;
			nearest_result.distance = left_intersection;
			nearest_result.success = true;
		}
	}

	if (right_intersection >= 0 && right_intersection < nearest_result.distance) {
		vec3 int_point = add_vec3(r->origin, scale_vec3_scalar(dir, right_intersection));
		Real point_inside_top = side_of_plane_point(int_point, top_plane);
		Real point_inside_bottom = side_of_plane_point(int_point, bottom_plane);
		Real point_inside_front = side_of_plane_point(int_point, forward_plane);
		Real point_inside_back = side_of_plane_point(int_point, backward_plane);

		if (point_inside_top < 0 && point_inside_bottom < 0 && point_inside_front < 0 && point_inside_back < 0) {
			nearest_result.position = int_point;
			nearest_result.normal = right_normal;
			nearest_result.distance = right_intersection;
			nearest_result.success = true;
		}
	}

	if (forward_intersection >= 0 && forward_intersection < nearest_result.distance) {
		vec3 int_point = add_vec3(r->origin, scale_vec3_scalar(dir, forward_intersection));
		Real point_inside_top = side_of_plane_point(int_point, top_plane);
		Real point_inside_bottom = side_of_plane_point(int_point, bottom_plane);
		Real point_inside_left = side_of_plane_point(int_point, left_plane);
		Real point_inside_right = side_of_plane_point(int_point, right_plane);

		if (point_inside_top < 0 && point_inside_bottom < 0 && point_inside_left < 0 && point_inside_right < 0) {
			nearest_result.position = int_point;
			nearest_result.normal = forward_normal;
			nearest_result.distance = forward_intersection;
			nearest_result.success = true;
		}
	}

	if (backward_intersection >= 0 && backward_intersection < nearest_result.distance) {
		vec3 int_point = add_vec3(r->origin, scale_vec3_scalar(dir, backward_intersection));
		Real point_inside_top = side_of_plane_point(int_point, top_plane);
		Real point_inside_bottom = side_of_plane_point(int_point, bottom_plane);
		Real point_inside_left = side_of_plane_point(int_point, left_plane);
		Real point_inside_right = side_of_plane_point(int_point, right_plane);

		if (point_inside_top < 0 && point_inside_bottom < 0 && point_inside_left < 0 && point_inside_right < 0) {
			nearest_result.position = int_point;
			nearest_result.normal = backward_normal;
			nearest_result.distance = backward_intersection;
			nearest_result.success = true;
		}
	}

	return nearest_result;
}

intersect_result ray_intersect_cylinder(ray* r, cylinder* c) {
	vec3 dir = normalize_vec3(r->direction);
	vec3 up = normalize_vec3(c->top_normal);
	vec3 down = scale_vec3_scalar(up, -1);
	Real half_height = c->height / 2;

	vec3 proj_dir_norm = project_vec3(dir, up);

	vec3 vecA = sub_vec3(dir, proj_dir_norm);
	vec3 d_p = sub_vec3(r->origin, c->position);
	vec3 proj_d_p_norm = project_vec3(d_p, up);
	vec3 d_p_proj_d_p = sub_vec3(d_p, proj_d_p_norm);

	Real A = dot_vec3(vecA, vecA);
	Real B = 2 * dot_vec3(vecA, d_p_proj_d_p);
	Real C = dot_vec3(d_p_proj_d_p, d_p_proj_d_p) - (c->radius * c->radius);

	Real t1 = (-B + sqrt((B * B) - (4 * A * C))) / (2 * A);
	Real t2 = (-B - sqrt((B * B) - (4 * A * C))) / (2 * A);

	if (t1 > 0 || t2 > 0) {
		vec3 point;
		bool on_surface = false;

		if (t1 < t2 && t1 > 0) {
			point = add_vec3(r->origin, scale_vec3_scalar(dir, t1));
			on_surface = true;
		}
		else if (t2 > 0) {
			point = add_vec3(r->origin, scale_vec3_scalar(dir, t2));
			on_surface = true;
		}

		if (on_surface) {
			vec3 point_normal_proj = project_vec3(sub_vec3(point, c->position), up);

			Real bound = mag_vec3(point_normal_proj);

			if (bound < half_height) {
				vec3 normal = sub_vec3(point, add_vec3(point_normal_proj, c->position));

				return (intersect_result) {
					point,
					normalize_vec3(normal),
					distance_vec3(point, r->origin),
					true
				};
			}
		}
	}

	vec3 top_point = add_vec3(c->position, scale_vec3_scalar(up, half_height));
	vec3 bottom_point = add_vec3(c->position, scale_vec3_scalar(down, half_height));

	Real top_intersect = ray_intersect_plane(*r, down, top_point);
	Real bottom_intersect = ray_intersect_plane(*r, up, bottom_point);

	if (top_intersect >= 0) {
		vec3 int_point = add_vec3(r->origin, scale_vec3_scalar(dir, top_intersect));
		Real dist = distance_vec3(int_point, top_point);

		if (dist <= c->radius) {
			return (intersect_result) {
				int_point,
				normalize_vec3(up),
				top_intersect,
				true
			};
		}
	}

	if (bottom_intersect >= 0) {
		vec3 int_point = add_vec3(r->origin, scale_vec3_scalar(dir, bottom_intersect));
		Real dist = distance_vec3(int_point, bottom_point);

		if (dist <= c->radius) {
			return (intersect_result) {
				int_point,
				normalize_vec3(down),
				bottom_intersect,
				true
			};
		}
	}

	return NULL_INTERSECTION;
}


void translate_sphere(sphere* s, vec3 v) {
	s->position = add_vec3(s->position, v);
}

void translate_box(box* b, vec3 v) {
	b->min = add_vec3(b->min, v);
	b->max = add_vec3(b->max, v);
}

void translate_cylinder(cylinder* c, vec3 v) {
	c->position = add_vec3(c->position, v);
}


void rotate_box(box* b, quat r) {
	b->min = rotate_vec3(b->min, r);
	b->max = rotate_vec3(b->max, r);
	b->top_normal = rotate_vec3(b->top_normal, r);
	b->front_normal = rotate_vec3(b->front_normal, r);
}

void rotate_cylinder(cylinder* c, quat r) {
	c->top_normal = rotate_vec3(c->top_normal, r);
}