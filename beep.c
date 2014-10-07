/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// Testing bell.

#include <stdio.h>

main () {
	int i = 1;
	while ((getchar() != 27) && (i != 50)) {
		printf("\a");
		i++;
	}
}
