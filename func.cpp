#include "func.h"

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
	uint32_t res, xres, sevres, xores, flag;
	res = left + righ;
	_asm
	{
		lahf
		mov[flag], eax
	}
	//проверка на переполнение
	xres = (res ^ left ^ righ) & 0x1010100;

	//Самая жесткая часть - вычитание res - xres
	sevres = (res | 0x808080) - (xres & 0x7F7F7F);
	xores = res ^ xres;
	res = ~((xores | 0x7F7F7F) ^ sevres) & ((((~xores & sevres) | (xores & res)) & 0x808080) >> 7) * 0xFF;

	res |= ((flag & 0x100) * 0xFF0000) | ((xres * 0xFF) >> 8);
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
