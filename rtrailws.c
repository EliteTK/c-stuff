// Remove trailing whitespace.
#include<stdio.h>

int main (int argc, char *argv[]) {
    char c;
    int spacecount = 0;
    while ( (c = getchar()) != EOF ) {
        if (c == ' ') {
            spacecount++;
        } else if (c == '\n' && spacecount) {
            putchar('\n');
            spacecount = 0;
        } else {
            if (spacecount) {
                int i;
                for (i = 0; i < spacecount; i++)
                    putchar(' ');
                spacecount = 0;
            }
            putchar(c);
        }
    }
}
