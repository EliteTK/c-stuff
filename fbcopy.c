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
#include<time.h>

int main(void) {
    FILE *fbp = fopen( "/dev/fb0", "r" );
    if (!fbp)
        exit(1);
    puts("Opened framebuffer for reading.");
    FILE *outfile = fopen( "/home/main/c-stuff/fbshot", "w" );
    if (!outfile)
        exit(1);
    puts("Opened outfile for writing.");
    char c;
    while ( (c = fgetc(fbp)) != EOF )
        fputc(c, outfile);
    puts("Finished writing to files. Closing.");
    fclose(fbp);
    fclose(outfile);
    puts("Finished.");
}
