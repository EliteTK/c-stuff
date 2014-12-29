#include <stdio.h>

int main()
{
	for (unsigned char i = 0; i < 128; i++)
		printf("%c%04x ", i, i);
	return 0;
}
