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
    for ( iii = 0; iii < 768 / 2; iii++ ) {
        for ( i = 0; i < 1024; i++ ) {
            fputc(0, fbp);
            fputc(255, fbp);
            fputc(0, fbp);
            fputc(255, fbp);
        }
        for ( i = 0; i < 1024; i++ ) {
            for ( ii = 0; ii < 4; ii++ )
                fputc(0, fbp);
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
