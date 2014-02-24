#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv[]) {
    char **string;

    string = malloc(100)
    *string = "test";

    printf("%s", **string);
}
