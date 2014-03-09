#include<stdio.h>

int main(int argc, const char *argv[]) {
    char *ptr = &main;
    int i;
    for (i = 0;; i++) {
        putchar(*(ptr+i));
    }
    return 0;
}
