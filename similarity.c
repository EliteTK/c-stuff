#include <errno.h>
#include <error.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	unsigned long matches = 0, misses = 0;
	char *strings[2];
	size_t lengths[2];
	size_t pos[2] = {0};
	unsigned current = 0;

	if (argc != 3)
		error(1, 0, "Incorrect number of arguments %d", argc);

	strings[0] = argv[1];
	lengths[0] = strlen(strings[0]);
	strings[1] = argv[2];
	lengths[1] = strlen(strings[1]);

	for (; pos[0] < lengths[0] && pos[1] < lengths[1];) {
		if (strings[0][pos[0]] == strings[1][pos[1]]) {
			matches++;
			pos[0]++;
			pos[1]++;
			current = current ? 0 : 1;
		} else {
			pos[current ? 0 : 1]++;
			misses++;
		}
	}

	if (lengths[0] > pos[0])
		misses += lengths[0] - pos[0] - 1;

	if (lengths[1] > pos[1])
		misses += lengths[1] - pos[1] - 1;

	printf("Matches: %lu, Misses: %lu\n", matches, misses);

	return 0;
}
