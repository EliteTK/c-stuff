#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[] ) {
    // malloc test
    char * string;
    string = (char *) malloc(10 * sizeof(char));

    *(string + 0) = 'a';
    *(string + 1) = 'b';
    *(string + 2) = 'c';
    *(string + 3) = '\n';
    *(string + 4) = '\0';

    printf("%s", string);

    free(string);
    string = NULL;
}
