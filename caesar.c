/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// This is the beginning of a caesar cipher program. Never got anywhere with it though.
#include<stdio.h>

int main ( int argc, char *argv[] ) {
    int i;
    for (i = 1; i < argc; i++) {
        printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
    }
}
