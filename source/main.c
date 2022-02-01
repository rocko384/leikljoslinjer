#include "geometry.h"
#include "scene.h"
#include "image.h"

#include <stdio.h>

int main(int argc, char** argv) {

	sphere sample_sphere1 = {
		{ 0, 0, 2 },
		1
	};

	color sphere1_color = { 1, 0, 0 };

	material sphere1_mat = {
		{ 1, 0, 0 },
		0.1,
		0,
		1
	};

	sphere sample_sphere2 = {
		{ 0, 0, -3 },
		1
	};

	material sphere2_mat = {
		{ 1, 1, 0 },
		0.1,
		0,
		1
	};

	box sample_box1 = {
		{ -5, -3, -5 },
		{ 5, -2, 5 },
		{ 0, 1, 0 }
	};

	material box1_mat = {
		{ 0, 0, 1 },
		0.05,
		0,
		1
	};

	box sample_box2 = {
		{-5, -2, 4},
		{5, 5, 5},
		{ 0, 1, 0 }
	};

	box sample_box3 = {
		{ -5, -2, -5 },
		{ -4, 5, 4 },
		{ 0, 1, 0 }
	};

	image test_image = create_image(2560, 1440);
	
	for (size_t x = 0; x < test_image.width; x++) {
		for (size_t y = 0; y < test_image.height; y++) {
			uint8_t r = (uint8_t)(((float)x) * 255.0 / test_image.width);
			uint8_t g = (uint8_t)(((float)y) * 255.0 / test_image.height);
			write_pixel(&test_image, x, y, (pixel) { r, g, 0 });
		}
	}

	write_image("testout.png", &test_image);

	camera test_camera = camera_lookat((vec3) { 7, 5, -5 }, (vec3) {0, 0, 0}, (vec3) {0, 1, 0}, 45);

	scene sample_scene;
	init_scene(&sample_scene, 5, 2);
	sample_scene.nodes[0] = CREATE_NODE(sphere, sample_sphere1, sphere1_mat, ray_intersect_sphere);
	sample_scene.nodes[1] = CREATE_NODE(sphere, sample_sphere2, sphere2_mat, ray_intersect_sphere);
	sample_scene.nodes[2] = CREATE_NODE(box, sample_box1, box1_mat, ray_intersect_box);
	sample_scene.nodes[3] = CREATE_NODE(box, sample_box2, box1_mat, ray_intersect_box);
	sample_scene.nodes[4] = CREATE_NODE(box, sample_box3, box1_mat, ray_intersect_box);

	sample_scene.lights[0] = create_point_light((color) { 1, 1, 1 }, (vec3) { 0, 4, 0 }, 18);
	sample_scene.lights[1] = create_point_light((color) { 1, 1, 1 }, (vec3) { 7, 0, 0 }, 20);

	render_scene(&sample_scene, &test_camera, &test_image);

	write_image("raytraceout.png", &test_image);

	destroy_scene(&sample_scene);
	destroy_image(test_image);

	return 0;
}