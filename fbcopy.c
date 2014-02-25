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
