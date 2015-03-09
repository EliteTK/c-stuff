#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	bool big_endian;

	union {
		uint32_t i;
		char c[4];
	} test = {0x01020304};

	big_endian = test.c[0] == 1;

	if (big_endian)
		printf("%s\n", "Big Endian");
	else
		printf("%s\n", "Small Endian");

	return EXIT_SUCCESS;
}
