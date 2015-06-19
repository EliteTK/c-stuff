/*
 * Copyright (C) 2014 - 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage: <text> <rotation>\a\n");
		exit(1);
	}

	int rot = strtol(argv[2], NULL, 10);
	unsigned length = strlen(argv[1]);

	for (unsigned i = 0; i < length; i++) {
		if (isalpha(argv[1][i])) {
			if (argv[1][i] - 'A' < 26)
				putchar((argv[1][i] - 'A' + rot) % 26 + 'A');
			else
				putchar((argv[1][i] - 'a' + rot) % 26 + 'a');
		} else
			putchar(argv[1][i]);
	}

	putchar('\n');

	return 0;
}
