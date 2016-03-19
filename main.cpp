#include <stdint.h>
#include <stdio.h>
#include <iostream>
using namespace std;

static uint32_t make_pixel(char r, char g, char b, char a = 0)
{
	return ((uint32_t)r << 24) |
		   ((uint32_t)g << 16) |
		   ((uint32_t)b << 8) |
	     	(uint32_t)a;
}

static uint32_t saturated_sum(uint32_t left, uint32_t right)
{
	uint32_t sum = left + right;
	if (sum > 0xFF)
		sum = 0xFF;
	return sum;
}

static uint32_t magic_sum(uint32_t left, uint32_t right)
{
	return ((bool)(0xFFFFFF00 & (left + right)) * 255) | ((left + right) & 255);
}

static uint32_t add_pixels(uint32_t left, uint32_t right)
{
	uint32_t r0 = (left >> 24) & 0xFF;
	uint32_t g0 = (left >> 16) & 0xFF;
	uint32_t b0 = (left >> 8) & 0xFF;
	uint32_t a0 = (left >> 0) & 0xFF;

	uint32_t r1 = (right >> 24) & 0xFF;
	uint32_t g1 = (right >> 16) & 0xFF;
	uint32_t b1 = (right >> 8) & 0xFF;
	uint32_t a1 = (right >> 0) & 0xFF;

	return make_pixel(saturated_sum(r0, r1), saturated_sum(g0, g1), saturated_sum(b0, b1), saturated_sum(a0, a1));
}

// Магическое сложение с насыщением
static uint32_t magic_add_pixels(uint32_t left, uint32_t right)
{
	uint32_t r0 = (left >> 24) & 0xFF;
	uint32_t g0 = (left >> 16) & 0xFF;
	uint32_t b0 = (left >> 8) & 0xFF;
	uint32_t a0 = (left >> 0) & 0xFF;

	uint32_t r1 = (right >> 24) & 0xFF;
	uint32_t g1 = (right >> 16) & 0xFF;
	uint32_t b1 = (right >> 8) & 0xFF;
	uint32_t a1 = (right >> 0) & 0xFF;
	return make_pixel(magic_sum(r0, r1), magic_sum(g0, g1), magic_sum(b0, b1), magic_sum(a0, a1));
}



int main()
{
	int i = 0;
	char test_bytes[23];
	for (int i = 0, j = 0 ; i < 0xFF; j++, i+=12)
		test_bytes[j] = i;

	for (char r0 : test_bytes) {
		for (char g0 : test_bytes) {
			for (char b0 : test_bytes) {
				for (char r1 : test_bytes) {
					for (char g1 : test_bytes) {
						for (char b1 : test_bytes) {
							i++;
							uint32_t pixel0 = make_pixel(r0, g0, b0);
							uint32_t pixel1 = make_pixel(r1, g1, b1);
							uint32_t magic_result = magic_add_pixels(pixel0, pixel1);
							uint32_t normal_result = add_pixels(pixel0, pixel1);
							if (normal_result != magic_result)
							{						
								printf("wrong result with [%08X]+[%08X]\n", pixel0, pixel1);
								printf("got [%08X] need [%08X]\n", magic_result, normal_result);						
							}
						}
					}
				}
			}
		}
	}
	printf("Everything is OK! i = %d\n", i);
	system("pause");
	return 0;
}