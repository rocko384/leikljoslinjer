#pragma once

#include "geometry.h"
#include "image.h"

#include <stddef.h>

typedef struct {
	vec3 position;
	vec3 direction;
	vec3 up;
	Real fov;
} camera;

typedef struct {
	Real r;
	Real g;
	Real b;
} color;

typedef struct {
	color color;
	Real reflectivity;
	Real transparency;
	Real refraction_index;
} material;

typedef struct {
	void* shape;
	intersect_func intersect;
	material material;
} scene_node;

enum light_type {
	point,
	directional,
	spotlight
};

typedef struct {
	enum light_type type;
	color color;
	vec3 position; // pointlight/spotlights only
	vec3 direction; // directional/spotlights only
	Real intensity;
	Real range_angle; // spotlights only
} scene_light;

camera camera_lookat(vec3 position, vec3 target, vec3 up, Real fov);

scene_node create_node(size_t shape_size_bytes, void* shape_data, material mat, intersect_func int_fn);
void destroy_node(scene_node node);

scene_light create_point_light(color color, vec3 position, Real intensity);
scene_light create_directional_light(color color, vec3 direction, Real intensity);
scene_light create_spotlight(color color, vec3 position, vec3 direction, Real intensity, Real range_angle);

#define CREATE_NODE(ShapeT, ShapeValue, Material, IntersectFunc) create_node(sizeof(ShapeT), &ShapeValue, Material, IntersectFunc)

typedef struct {
	scene_node* nodes;
	size_t node_count;
	scene_light* lights;
	size_t light_count;
} scene;

void init_scene(scene* s, size_t num_nodes, size_t num_lights);
void destroy_scene(scene* s);

void render_scene(scene* s, camera* c, image* i, size_t thread_count);