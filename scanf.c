#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *input;
	scanf("%ms", &input);

	printf("%s", input);
	free(input);

	return EXIT_SUCCESS;
}
