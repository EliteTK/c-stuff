/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include<stdio.h>

_Bool isOdd( int );

int main ( int argc, char *argv[] ) {
    if ( argc == 2 ) {
        printf("%s\n", isOdd( atoi( argv[1] ) ) ? "true" : "false" );
        return 0;
    } else {
        printf("Usage: '%s <number>'\n", argv[0]);
        return 1;
    }
}

_Bool isOdd( int n ) {
    return n % 2;
}
