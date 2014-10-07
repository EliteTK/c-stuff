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

int main( int argc, char *argv[] ) {
    if ( argc != 5 ) {
        printf("Usage %s <red> <green> <blue> <alpha>\n", argv[0]);
        return 1;
    }

    unsigned char red = atoi( argv[1] );
    unsigned char green = atoi( argv[2] );
    unsigned char blue = atoi( argv[3] );
    unsigned char alpha = atoi( argv[4] );

    unsigned int colour = alpha << 24 | red << 16 | green << 8 | blue;

    printf("R: %u G: %u B: %u A: %u\nColour value: %u\n", red , green, blue, alpha, colour);
}
