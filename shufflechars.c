/*
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

static inline unsigned rand_to_max(unsigned max)
{
	double random;

	while ((random = rand()) == (double)RAND_MAX);

	return random / (double)RAND_MAX * (double)max;
}

int main(int argc, char **argv)
{
	size_t length;
	char *text, *dest;

	srand(time(NULL));

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <text>\a\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	text = argv[1];
	length = strlen(text);

	bool relocated[length];

	memset(relocated, 0, length);
	dest = malloc(length + 1);

	for (size_t i = 0; i < length; i++) {
		size_t index;
		while (index = rand_to_max(length), relocated[index])
			;

		dest[i] = text[index];
		relocated[index] = true;
	}

	dest[length] = '\0';

	printf("%s\n", dest);

	return EXIT_SUCCESS;
}
