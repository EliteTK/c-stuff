/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <time.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
	struct timespec tsp = {
		.tv_sec = 0,
		.tv_nsec = 500*1000*1000
	};

	while (true) {
		static int i = 0;
		printf("\r%d", i);
		fflush(stdout);
		nanosleep(&tsp, NULL);
		i++;
	}
	return 0;
}
