// This is the beginning of a caesar cipher program. Never got anywhere with it though.
#include<stdio.h>

int main ( int argc, char *argv[] ) {
    int i;
    for (i = 1; i < argc; i++) {
        printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
    }
}
