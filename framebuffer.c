#include<stdio.h>
#include<stdlib.h>

int main( void ) {
    printf("Here goes nothing!");
    getchar();
    FILE *fbp = fopen( "/dev/fb0", "w");
    int i;
    for( i = 0; i < 1044480; i++ )
        fputc(i, fbp);
    fclose( fbp );
}


