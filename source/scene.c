#include "scene.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RENDER_DISTANCE 100.0
#define MAX_REFLECTIONS 16

camera camera_lookat(vec3 position, vec3 target, vec3 up, Real fov) {
	vec3 direction = normalize_vec3(sub_vec3(target, position));

	return (camera) {
		position,
		direction,
		up,
		fov
	};
}

scene_node create_node(size_t shape_size_bytes, void* shape_data, material mat, intersect_func int_fn) {
	scene_node ret;
	ret.shape = malloc(shape_size_bytes);
	memcpy(ret.shape, shape_data, shape_size_bytes);
	ret.intersect = int_fn;
	ret.material = mat;

	return ret;
}

void destroy_node(scene_node node) {
	free(node.shape);
}

scene_light create_point_light(color color, vec3 position, Real intensity) {
	return (scene_light) {
		point,
		color,
		position,
		{ 0, 0, 0 },
		intensity,
		0
	};
}

scene_light create_directional_light(color color, vec3 direction, Real intensity) {
	return (scene_light) {
		directional,
		color,
		{ 0, 0, 0 },
		direction,
		intensity,
		0
	};
}

scene_light create_spotlight(color color, vec3 position, vec3 direction, Real intensity, Real range_angle) {
	return (scene_light) {
		spotlight,
		color,
		position,
		direction,
		intensity,
		range_angle
	};
}

void init_scene(scene* s, size_t num_nodes, size_t num_lights) {
	s->nodes = malloc(num_nodes * sizeof(scene_node));
	s->lights = malloc(num_lights * sizeof(scene_light));
	memset(s->nodes, 0, num_nodes * sizeof(scene_node));
	memset(s->lights, 0, num_lights * sizeof(scene_light));
	s->node_count = num_nodes;
	s->light_count = num_lights;
}

void destroy_scene(scene* s) {
	for (size_t i = 0; i < s->node_count; i++) {
		if (s->nodes[i].shape != NULL) {
			destroy_node(s->nodes[i]);
		}
	}

	free(s->nodes);
	free(s->lights);
}

typedef struct {
	color color;
	vec3 incidence_vector;
} light_cast_result;

light_cast_result ray_cast_light(scene* s, vec3 position, scene_light l) {
	intersect_result light_result = {
		l.position,
		{ 0, 0, 0 },
		mag2_vec3(sub_vec3(l.position, position)),
		true
	};

	vec3 incidence_vec = sub_vec3(l.position, position);

	ray r = {
		position,
		normalize_vec3(incidence_vec)
	};

	for (size_t shape = 0; shape < s->node_count; shape++) {
		if (s->nodes[shape].shape != NULL) {
			intersect_result result = s->nodes[shape].intersect(&r, s->nodes[shape].shape);

			if (result.success && result.distance < light_result.distance) {
				return (light_cast_result) { { 0, 0, 0 }, { 0, 0, 0 } };
			}
		}
	}

	Real d2 = mag2_vec3(incidence_vec);
	Real r2 = l.intensity * l.intensity;
	Real intensity = clamp(1 - (d2 / r2), 0, 1);
	intensity *= intensity;
	return (light_cast_result) { { l.color.r * intensity, l.color.g * intensity, l.color.b * intensity }, incidence_vec };
}

color get_illuminated_color(scene* s, color c, vec3 position, vec3 normal) {
	color accumulator = { 0, 0, 0 };

	for (size_t light = 0; light < s->light_count; light++) {
		scene_light curr_light = s->lights[light];

		light_cast_result light_result = ray_cast_light(s, position, curr_light);

		Real cos_theta = fmax(0, dot_vec3(normalize_vec3(light_result.incidence_vector), normal));

		color diffuse = { light_result.color.r * c.r * cos_theta, light_result.color.g * c.g * cos_theta, light_result.color.b * c.b * cos_theta };
		accumulator = (color){ fmax(accumulator.r, diffuse.r), fmax(accumulator.g, diffuse.g), fmax(accumulator.b, diffuse.b) };
	}

	return (color){ fmin(accumulator.r, 1), fmin(accumulator.g, 1), fmin(accumulator.b, 1) };
}

color ray_cast(scene* s, ray r, size_t reflection_count) {
	intersect_result nearest_result = {
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		MAX_RENDER_DISTANCE,
		false
	};

	color result_color = { 0, 0, 0 };
	size_t result_shape = 0;

	for (size_t shape = 0; shape < s->node_count; shape++) {
		if (s->nodes[shape].shape != NULL) {
			intersect_result result = s->nodes[shape].intersect(&r, s->nodes[shape].shape);

			if (result.success && result.distance < nearest_result.distance) {
				nearest_result = result;
				result_color = s->nodes[shape].material.color;
				result_shape = shape;
			}
		}
	}

	if (nearest_result.success) {
		color  c = get_illuminated_color(s, result_color, nearest_result.position, nearest_result.normal);

		if (s->nodes[result_shape].material.reflectivity > 0 && reflection_count > 0) {
			vec3 reflection = reflect(r.direction, nearest_result.normal);
			Real reflectivity = s->nodes[result_shape].material.reflectivity;

			ray reflect_ray = {
				nearest_result.position,
				reflection
			};

			color reflected_color = ray_cast(s, reflect_ray, reflection_count - 1);

			c = (color){ c.r + (reflected_color.r * reflectivity), c.g + (reflected_color.g * reflectivity), c.b + (reflected_color.b * reflectivity) };
		}

		return c;
	}

	return (color) { 0, 0, 0 };
}

void render_scene(scene* s, camera* c, image* i) {
	// Calc eye coords in world space
	Real aspect = ((Real)i->width) / ((Real)i->height);
	Real half_w = aspect / 2;
	Real fov_2 = c->fov / 2;
	Real eye_dist = -(half_w / tan(fov_2));
	vec3 eye_dir = normalize_vec3(c->direction);
	vec3 eye_pos = add_vec3(c->position, scale_vec3_scalar(eye_dir, eye_dist));
	vec3 right = normalize_vec3(cross_vec3(c->up, eye_dir));
	vec3 up = normalize_vec3(cross_vec3(eye_dir, right));

	for (size_t x = 0; x < i->width; x++) {
		for (size_t y = 0; y < i->height; y++) {
			Real rel_x = (((Real)x) / ((Real)i->width)) - 0.5;
			rel_x *= 2;
			rel_x *= aspect;
			Real rel_y = (((Real)y) / ((Real)i->height)) - 0.5;
			rel_y *= -2;

			vec3 right_vec = scale_vec3_scalar(right, rel_x);
			vec3 up_vec = scale_vec3_scalar(up, rel_y);
			vec3 offset_vec = add_vec3(right_vec, up_vec);
			vec3 origin = add_vec3(c->position, offset_vec);

			ray r = {
				origin,
				normalize_vec3(sub_vec3(origin, eye_pos))
			};

			color c = ray_cast(s, r, 16);

			pixel outcolor = {
				c.r * 255.0,
				c.g * 255.0,
				c.b * 255.0
			};

			write_pixel(i, x, y, outcolor);
		}
	}
}