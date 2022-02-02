#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel;

typedef struct {
	size_t width;
	size_t height;
	pixel* pixels;
} image;

image create_image(size_t width, size_t height);
void destroy_image(image i);

void write_pixel(image* i, size_t x, size_t y, pixel p);
pixel read_pixel(image* i, size_t x, size_t y);

void write_image(const char* file, image* i);