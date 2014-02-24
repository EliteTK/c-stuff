// Your guess is as good as mine. Possibly something to do with GNU Getline though...
#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv[]) {
    char **string;

    string = malloc(100)
    *string = "test";

    printf("%s", **string);
}
