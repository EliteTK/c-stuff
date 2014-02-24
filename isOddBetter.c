// Trying to see the differences between assembly created using different odd checks.
// This taught me that the compiler is less stupid than I thought it was. The final test
// is ommited from this directory because it involved two cluttery small files. But it
// proved that the compiler does not automatically do odd checks the faster way.
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
    // Bitwise and with LSB to check if number is odd or even.
    // LSB == 0 => even
    // LSB == 1 => odd
    return n & 1;
}