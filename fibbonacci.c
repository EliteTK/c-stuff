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
