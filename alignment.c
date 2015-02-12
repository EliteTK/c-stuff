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

struct misaligned {
	char ca;
	long la;

	char cb;
	long lb;

	char cc;
	long lc;

	char cd;
	long ld;

	char ce;
	long le;

	char cf;
	long lf;

	char cg;
	long lg;

	char ch;
	long lh;
};

struct aligned {
	char ca;
	char cb;
	char cc;
	char cd;
	char ce;
	char cf;
	char cg;
	char ch;

	long la;
	long lb;
	long lc;
	long ld;
	long le;
	long lf;
	long lg;
	long lh;
};

int main(void)
{
	printf("sizeof misaligned: %d, sizeof aligned %d\n", sizeof(struct
				misaligned), sizeof(struct aligned));

	return EXIT_SUCCESS;
}
