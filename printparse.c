// In collaboration with clone.c this was meant to turn clone.c's code into something I
// could paste back into clone.c.
#include<stdio.h>

int main ( int argc, char *argv[] ) {
    char c;
    while ( (c = getchar()) != EOF ) {
        switch (c) {
            case '\n' :
                printf("\\n");
                break;
            case '\t' :
                printf("\\t");
                break;
            case '\\' :
                printf("\\\\");
                break;
            default :
                putchar(c);
                break;
        }
    }
}
