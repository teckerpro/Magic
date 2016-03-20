#include <stdint.h>
#include <stdio.h>
#include <iostream>
using namespace std;

static uint32_t make_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0)
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

// Магическое сложение с насыщением
static uint32_t magic_add_pixels(uint32_t left, uint32_t right)
{
	uint32_t res = 0;
	
	res += (((bool)(0x0000100 & (left & 0x0000FF) + (right & 0x0000FF))) * 0x0000FF) | ((left & 0x0000FF) + (right & 0x0000FF) & 0x0000FF);
	res += (((bool)(0x0010000 & (left & 0x00FF00) + (right & 0x00FF00))) * 0x00FF00) | ((left & 0x00FF00) + (right & 0x00FF00) & 0x00FF00);
	res += (((bool)(0x1000000 & (left & 0xFF0000) + (right & 0xFF0000))) * 0xFF0000) | ((left & 0xFF0000) + (right & 0xFF0000) & 0xFF0000);
	res += ((((bool)(0x0000100 & (left>>24 & 0x0000FF) + (right>>24 & 0x0000FF))) * 0x0000FF) | ((left>>24 & 0x0000FF) + (right>>24 & 0x0000FF) & 0x0000FF))<<24;

	return res;
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

int main()

{
	int i = 0;
	uint8_t test_bytes[26];
	for (int i = 0, j = 0 ; i < 0xFF; j++, i+=10)
		test_bytes[j] = i;

	for (uint8_t r0 : test_bytes) {
		for (uint8_t g0 : test_bytes) {
			for (uint8_t b0 : test_bytes) {
				for (uint8_t r1 : test_bytes) {
					for (uint8_t g1 : test_bytes) {
						for (uint8_t b1 : test_bytes) {
							i++;
							uint32_t pixel0 = make_pixel(r0, g0, b0);
							uint32_t pixel1 = make_pixel(r1, g1, b1);
							uint32_t magic_result = magic_add_pixels(pixel0, pixel1);
							uint32_t normal_result = add_pixels(pixel0, pixel1);
							if (normal_result != magic_result)
							{						
								printf("wrong result with [%08X]+[%08X]\n", pixel0, pixel1);
								printf("got [%08X] need [%08X]\n", magic_result, normal_result);
								return -1;
							}
						}
					}
				}
			}
		}
	}
	printf("Everything is OK! Number of iterations is = %d\n", i);

	system("pause");
	return 0;
}