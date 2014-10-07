/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// In collaboration with clone.c this was meant to turn clone.c's code into something I
// could paste back into clone.c.
#include<stdio.h>

int main ( int argc, char *argv[] ) {
    char c;
    while ( (c = getchar()) != EOF ) {
        switch (c) {
            case '\n' :
                printf("\\n");
                break;
            case '\t' :
                printf("\\t");
                break;
            case '\\' :
                printf("\\\\");
                break;
            default :
                putchar(c);
                break;
        }
    }
}
