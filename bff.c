// Generated with TK's "fuck" brainfuck to C parser.
#include<stdio.h>
#include<stdlib.h>

int main() {
    char *ptrt;
    ptrt = calloc(1000, sizeof(char));
    char *ptr;
    ptr = ptrt;
    // The following is directly parsed
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    while (*ptr) {
        ++ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        --ptr;
        --ptr;
        --*ptr;
    }
    ++ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    putchar(*ptr);
    ++ptr;
    ++*ptr;
    putchar(*ptr);
    --*ptr;
    --*ptr;
    --*ptr;
    putchar(*ptr);
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    putchar(*ptr);
    --*ptr;
    --*ptr;
    putchar(*ptr);
    --ptr;
    putchar(*ptr);
    ++ptr;
    ++ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    while (*ptr) {
        --*ptr;
        --ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++ptr;
    }
    --ptr;
    ++*ptr;
    putchar(*ptr);
    --*ptr;
    --*ptr;
    --*ptr;
    putchar(*ptr);
    --*ptr;
    --*ptr;
    --*ptr;
    putchar(*ptr);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    putchar(*ptr);
    // Closing cleanup
    free(ptrt);
    putchar('\n');
    return 0;
}
