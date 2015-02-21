#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *input;

	scanf("%ms", &input);

	if (strcmp(input, "Test") == 0)
		printf("Match\n");
	else
		printf("Fail\n");

	free(input);

	return EXIT_SUCCESS;
}
