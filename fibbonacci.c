#include <stdio.h>

int main(/*int argc, char **argv*/) {
	int a = 0, b = 1, c = 0;

	do {
		printf("%d, ", a);
		a = b + c;
		c = b;
		b = a;
	} while (a < 100);
	return 0;
}
