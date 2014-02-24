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
