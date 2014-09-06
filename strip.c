#include <stdio.h>

int main(int argc, char **argv)
{
    int c;
    while((c = getchar()) != EOF)
        if(isdigit(c) || c == '\n')
            putchar(c);
}
