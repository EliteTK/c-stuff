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
#include <string.h>
#include <ctype.h>

#define CTOI(c) ((c) - 'A')
#define ITOC(c) ((c) + 'A')

#define ALPHACHARS 26

void preprocess(char *str)
{
	char *src = str, *dest = str;

	while (*src != '\0') {
		if (isalpha(*src))
			*(dest++) = toupper(*src);
		src++;
	}

	*dest = '\0';
}

double calc_ic_column(const char *text, size_t length, size_t offset, size_t spacing)
{
	unsigned foundc[ALPHACHARS] = {0}, total_chars = 0;
	unsigned long pre_sum = 0;

	for (size_t i = offset; i < length; i += spacing, total_chars++)
		foundc[CTOI(text[i])]++;

	for (unsigned i = 0; i < ALPHACHARS; i++)
		pre_sum += foundc[i] * (foundc[i] - 1);

	return (double)pre_sum / ((double)total_chars * (double)(total_chars - 1) / ALPHACHARS);
}

double calc_ic(const char *text, size_t length, size_t width)
{
	double total = 0;

	for (size_t offset = 0; offset < width; offset++)
		total += calc_ic_column(text, length, offset, width);

	return total / width;
}

int main(int argc, char **argv)
{
	char *text;
	size_t length;
	unsigned long max;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <text> <max>\a\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	text = argv[1];
	max = strtoul(argv[2], NULL, 10);

	preprocess(text);
	length = strlen(text);

	for (unsigned long spacing = 1; spacing <= max; spacing++) {
		double ic = calc_ic(text, length, spacing);
		unsigned barlen;

		if (ic > 0.8 && ic < 4)
			barlen = (ic - 0.8) / 3.2 * 40.0;
		else
			barlen = ic <= 0.8 ? 0 : 40;

		printf("%3lu - %6.3f ", spacing, ic);
		for (unsigned i = 0; i < barlen; i++)
			putchar('#');
		putchar('\n');
	}

	return EXIT_SUCCESS;
}
