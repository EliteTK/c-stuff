#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    char c;
    while((c = getchar()) != EOF)
        putchar((char)((double)rand() / (double)RAND_MAX * (double)256));
}
