#include "geometry.h"
#include "scene.h"
#include "image.h"

#include <stdio.h>

int main(int argc, char** argv) {

	sphere sample_sphere1 = UNIT_SPHERE;

	translate_sphere(&sample_sphere1, (vec3) { 0, 0, 2 });

	material sphere1_mat = {
		{ 1, 0, 0 },
		0.3,
		0,
		1
	};

	sphere sample_sphere2 = UNIT_SPHERE;

	translate_sphere(&sample_sphere2, (vec3) { 0, 0, -3 });

	material sphere2_mat = {
		{ 1, 1, 0 },
		0.01,
		0,
		1
	};


	box box1 = UNIT_BOX;

	rotate_box(&box1, rotate_on_axis((vec3) { 1, 1, 1 }, 45));
	translate_box(&box1, (vec3) { 3, 0, 0 });

	material box1_mat = {
		{ 0.5, 0.1, 0.6 },
		0.3,
		0,
		1
	};


	box floor = {
		{ -5, -3, -5 },
		{ 5, -2, 5 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	};

	box wall1 = {
		{-5, -2, 4},
		{5, 5, 5},
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	};

	box wall2 = {
		{ -5, -2, -5 },
		{ -4, 5, 4 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	};

	material stage_mat = {
		{ 0, 0, 1 },
		0.05,
		0,
		1
	};

	image test_image = create_image(3840, 2160);
	
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
	init_scene(&sample_scene, 6, 2);
	sample_scene.nodes[0] = CREATE_NODE(box, floor, stage_mat, ray_intersect_box);
	sample_scene.nodes[1] = CREATE_NODE(box, wall1, stage_mat, ray_intersect_box);
	sample_scene.nodes[2] = CREATE_NODE(box, wall2, stage_mat, ray_intersect_box);
	sample_scene.nodes[3] = CREATE_NODE(sphere, sample_sphere1, sphere1_mat, ray_intersect_sphere);
	sample_scene.nodes[4] = CREATE_NODE(sphere, sample_sphere2, sphere2_mat, ray_intersect_sphere);
	sample_scene.nodes[5] = CREATE_NODE(box, box1, box1_mat, ray_intersect_box);

	sample_scene.lights[0] = create_point_light((color) { 1, 1, 1 }, (vec3) { 0, 10, 0 }, 18);
	sample_scene.lights[1] = create_point_light((color) { 1, 1, 1 }, (vec3) { 7, 0, 0 }, 20);

	render_scene(&sample_scene, &test_camera, &test_image, 12);

	write_image("raytraceout.png", &test_image);

	destroy_scene(&sample_scene);
	destroy_image(test_image);

	return 0;
}