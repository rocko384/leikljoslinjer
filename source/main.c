#include "geometry.h"
#include "scene.h"
#include "image.h"

#include <stdio.h>

int main(int argc, char** argv) {

	ray sample_ray1 = {
		{ 0, 0, 0 },
		normalize_vec3((vec3) { 0, 0, 1 })
	};

	ray sample_ray2 = {
		{ 0, 0, 0 },
		normalize_vec3((vec3) { 0, 0, -1 })
	};

	ray sample_ray3 = {
		{ 0, 0, 0 },
		normalize_vec3((vec3) { 0, 0.1, 1 })
	};

	sphere sample_sphere1 = {
		{ 0, 0, 2 },
		1
	};

	color sphere1_color = { 1, 0, 0 };

	sphere sample_sphere2 = {
		{ 0, 0, -3 },
		1
	};

	color sphere2_color = { 1, 1, 0 };

	image test_image = create_image(1920, 1080);
	
	for (size_t x = 0; x < test_image.width; x++) {
		for (size_t y = 0; y < test_image.height; y++) {
			uint8_t r = (uint8_t)(((float)x) * 255.0 / test_image.width);
			uint8_t g = (uint8_t)(((float)y) * 255.0 / test_image.height);
			write_pixel(&test_image, x, y, (pixel) { r, g, 0 });
		}
	}

	write_image("testout.png", &test_image);

	camera test_camera = camera_lookat((vec3) { 5, 5, -5 }, (vec3) {0, 0, 0}, (vec3) {0, 1, 0}, 45);

	scene sample_scene;
	init_scene(&sample_scene, 2, 1);
	sample_scene.nodes[0] = CREATE_NODE(sphere, sample_sphere1, sphere1_color, ray_intersect_sphere);
	sample_scene.nodes[1] = CREATE_NODE(sphere, sample_sphere2, sphere2_color, ray_intersect_sphere);

	sample_scene.lights[0] = create_point_light((color) { 1, 1, 1 }, (vec3) { -3, 0, 0 }, 6);

	render_scene(&sample_scene, &test_camera, &test_image);

	write_image("raytraceout.png", &test_image);

	destroy_scene(&sample_scene);
	destroy_image(test_image);

	return 0;
}