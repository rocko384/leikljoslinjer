#include "image.h"

#include <stb_image_write.h>

#include <stdlib.h>
#include <string.h>

image create_image(size_t width, size_t height) {
	image ret = {
		width,
		height,
		malloc(width * height * sizeof(pixel))
	};

	memset(ret.pixels, 0, width * height * sizeof(pixel));

	return ret;
}

void destroy_image(image i) {
	free(i.pixels);
}

void write_pixel(image* i, size_t x, size_t y, pixel p) {
	size_t idx = (y * i->width) + x;
	i->pixels[idx] = p;
}

pixel read_pixel(image* i, size_t x, size_t y) {
	size_t idx = (y * i->width) + x;
	return i->pixels[idx];
}

void write_image(const char* file, image* i) {
	stbi_write_png(file, i->width, i->height, sizeof(pixel), i->pixels, i->width * sizeof(pixel));
}