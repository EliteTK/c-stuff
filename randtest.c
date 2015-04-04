/*
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FROM 0
#define TO   9

int8_t randrange(int8_t from, int8_t to)
{
	int base_random = rand();
	if (RAND_MAX == base_random) return randrange(from, to);
	int range = to - from,
	    remainder = RAND_MAX % range,
	    bucket = RAND_MAX / range;
	if (base_random < RAND_MAX - remainder) {
		return from + base_random/bucket;
	} else {
		return randrange(from, to);
	}
}


static unsigned rand_to_max(unsigned max)
{
	double random;

	while ((random = rand()) == (double)RAND_MAX);

	return random / (double)RAND_MAX * (double)max;
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	uint64_t counter[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (int i = 0; i < 1000000; i++)
		counter[rand_to_max(9)]++;

	for (int i = 0; i < 10; i++)
		printf("%d: %lu\n", i, counter[i]);

	return EXIT_SUCCESS;
}
