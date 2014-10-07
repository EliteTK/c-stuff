/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// Remove trailing whitespace.
#include<stdio.h>

int main (int argc, char *argv[]) {
    char c;
    int spacecount = 0;
    while ( (c = getchar()) != EOF ) {
        if (c == ' ') {
            spacecount++;
        } else if (c == '\n' && spacecount) {
            putchar('\n');
            spacecount = 0;
        } else {
            if (spacecount) {
                int i;
                for (i = 0; i < spacecount; i++)
                    putchar(' ');
                spacecount = 0;
            }
            putchar(c);
        }
    }
}
