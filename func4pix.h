#pragma once
#include <stdint.h>
#include <stdio.h>

 uint32_t make_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0);
 uint32_t saturated_sum(uint32_t left, uint32_t right);
// Магическое сложение с насыщением
 uint32_t magic_add_pixels(uint32_t left, uint32_t righ);
 uint32_t add_pixels(uint32_t left, uint32_t right);
