
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

#define harray(type, name, x, y) type (*name)[y] = malloc(sizeof(type) * x * y)

int main(/*int argc, char **argv*/)
{
	/*int (*test)[5] = malloc(sizeof(int) * 5 * 10);*/
	/*harray(int, test, 10, 5);*/

	/*for (int i = 0; i < 10; i++)*/
		/*for (int ii = 0; ii < 5; ii++) {*/
			/*test[i][ii] = i * ii;*/
			/*printf("%d, ", i * ii);*/
		/*}*/
	/*putchar('\n');*/

	/*for (int i = 0; i < 10 * 5; i++)*/
		/*printf("%d, ", *(((int *)test) + i));*/
	/*putchar('\n');*/

	int test[10][5] = {
		{1, 2, 3, 4, 5},
		{4, 1, 6, 7, 8},
		{9, 7, 7, 4, 0},
		{7, 0, 4, 2, 9},
		{3, 9, 3, 3, 8},
		{4, 3, 1, 4, 7},
		{5, 2, 2, 6, 6},
		{0, 3, 3, 7, 5},
		{1, 4, 4, 7, 4},
		{2, 7, 0, 8, 3}};

	for (int i = 0; i < 5 * 10; i++)
		printf("%d, ", ((int *)test)[i]);

	putchar('\n');

	/* int *another = (int *){1, 2, 4, 6};*/

	/*for (int i = 0; i < 4; i++)*/
		/*printf("%d, ", another[i]);*/

	putchar('\n');

	/*free(test);*/
	return 0;
}
