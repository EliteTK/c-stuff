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

int main(int argc, char **argv)
{
    srand(time(NULL));
    char c;
    while((c = getchar()) != EOF)
        putchar((char)((double)rand() / (double)RAND_MAX * (double)256));
}
