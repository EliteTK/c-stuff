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
#include<stdlib.h>

#define SSIZE 3145728
#define INFILE "/home/main/c-stuff/fbshot"

int main( void ) {
    FILE *fbp = fopen( "/dev/fb0", "w" );
    if (!fbp) {
        puts("Failed to open /dev/fb0");
        exit(1);
    }

    FILE *infile = fopen( INFILE, "r" );
    if (!infile) {
        printf("Failed to open %s\n", INFILE);
        exit(1);
    }

    int i, ii, iii;
    for ( iii = 0; iii < 768 / 3; iii++ ) {
        for ( i = 0; i < 1024; i++ ) {
            fputc(255, fbp);
            fputc(0, fbp);
            fputc(0, fbp);
            fputc(255, fbp);
        }
        for ( i = 0; i < 1024; i++ ) {
            fputc(0, fbp);
            fputc(255, fbp);
            fputc(0, fbp);
            fputc(255, fbp);
        }
        for ( i = 0; i < 1024; i++ ) {
            fputc(0, fbp);
            fputc(0, fbp);
            fputc(255, fbp);
            fputc(255, fbp);
        }
    }

    /*
    char c;
    while((c = fgetc(infile)) != EOF)
        fputc(c, fbp);
    */
    fclose( fbp );
    fclose( infile );
}
