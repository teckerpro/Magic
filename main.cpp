#include "func.h"
#include "test.h"
#include <stdint.h>
#include <iostream>

int main()
{

	uint32_t(*pmagic)(uint32_t, uint32_t) = &magic_add_pixels;

	testfunc(pmagic);

	system("pause");
	return 0;
}