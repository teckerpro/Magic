#include "func4pix.h"

 uint32_t make_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)r << 0) |
		((uint32_t)g << 8) |
		((uint32_t)b << 16) |
		(uint32_t)a << 24;
}

 uint32_t saturated_sum(uint32_t left, uint32_t right)
{
	uint32_t sum = left + right;
	if (sum > 0xFF)
		sum = 0xFF;
	return sum;
}

// Магическое сложение с насыщением
 uint32_t magic_add_pixels(uint32_t left, uint32_t righ)
{
	uint32_t res, xres;
	res = left + righ;
	//проверка на переполнение
	xres = (res ^ left ^ righ) & 0x1010100;
	//вычитание
	res = res - xres & 0xff | res - xres & 0xff00 | res - (xres & 0xff0000) & 0xff0000;
	res |= ((xres * 0xFF) >> 8);
	return res;
}

 uint32_t add_pixels(uint32_t left, uint32_t right)
{
	uint32_t r0 = (left >> 0) & 0xFF;
	uint32_t g0 = (left >> 8) & 0xFF;
	uint32_t b0 = (left >> 16) & 0xFF;
	uint32_t a0 = (left >> 24) & 0xFF;

	uint32_t r1 = (right >> 0) & 0xFF;
	uint32_t g1 = (right >> 8) & 0xFF;
	uint32_t b1 = (right >> 16) & 0xFF;
	uint32_t a1 = (right >> 24) & 0xFF;

	return make_pixel(saturated_sum(r0, r1), saturated_sum(g0, g1), saturated_sum(b0, b1), saturated_sum(a0, a1));
}
