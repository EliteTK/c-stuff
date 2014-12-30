/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	unsigned char subst[4][256];
	unsigned char lastval[] = {249, 20, 174, 199}; /* Offsets */

	/* Generate substitution tables. */
	for (int i = 0; i < 256; i++) {
		for (int ii = 0; ii < 4; ii++)
			subst[ii][i] = lastval[ii];

		if (i % 8 == 7) lastval[0] -= 13;
		else lastval[0] += i & 1 ? 3 : -1;

		if (i % 8 == 7) lastval[1] += 9;
		else if ((i + 4) % 8 == 7) lastval[1] -=7;
		else lastval[1] += 1;

		if (i % 16 == 15) lastval[2] += 29;
		else lastval[2] += i & 1 ? -3 : 1;

		if (i % 8 == 7) lastval[3] += 15;
		else lastval[3] -= 1;
	}

	/* Decode */
	int c;
	int pos = argc > 1 ? strtol(argv[1], NULL, 10) : 0;
	while ((c = getchar()) != EOF) {
		for (int i = 0; i < 256; i++)
			if (subst[pos%4][i] == c) {
				if (isascii(i)) putchar(i);
				break;
			}
		pos++;
	}

	return 0;
}
