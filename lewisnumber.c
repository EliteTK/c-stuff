#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main ( int argc, char *argv[] ) {
    srand( time(NULL) );
    printf("Lewis, your number is %d.\n", rand());
}
