#include "test.h"
#include "func4pix.h"
#include <stdio.h>
#include <iostream>

void testfunc(uint32_t(*fp)(uint32_t, uint32_t))
{
	int i = 0;
	uint8_t test_bytes[] = { 0x0, 0x1, 0x2, 0x3, 0x5, 0xA, 0xF, 0x10, 0x5F, 0x6E, 0x80, 0xB0, 0xDB, 0xA0, 0xCD, 0xF0, 0xF1, 0xEE, 0xE0, 0xE8, 0xEF, 0xFE, 0xFC, 0xFF };

	for (uint8_t r0 : test_bytes) {
		for (uint8_t g0 : test_bytes) {
			for (uint8_t b0 : test_bytes) {
				for (uint8_t r1 : test_bytes) {
					for (uint8_t g1 : test_bytes) {
						for (uint8_t b1 : test_bytes) {
							i++;
							uint32_t pixel0 = make_pixel(r0, g0, b0);
							uint32_t pixel1 = make_pixel(r1, g1, b1);
							uint32_t magic_result = fp(pixel0, pixel1);
							uint32_t normal_result = add_pixels(pixel0, pixel1);
							if (normal_result != magic_result)
							{
								printf("wrong result with [%08X]+[%08X]\n", pixel0, pixel1);
								printf("got [%08X] need [%08X]\n", magic_result, normal_result);
								system("pause");
							}
						}
					}
				}
			}
		}
	}
	printf("Everything is OK! Number of iterations is = %d\n", i);
}