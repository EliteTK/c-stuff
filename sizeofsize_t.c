// Really self explanatory.
#include<stdio.h>
#include<stdlib.h>

int main ( int argc, char *argv[] ) {
    int size = sizeof(size_t);
    printf("The size of size_t is %dB or %db\n", size, size * 8);
}
