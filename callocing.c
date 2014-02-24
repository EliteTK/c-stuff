// Deja-vu?
#include<stdio.h>
#include<stdlib.h>

int main() {
    int *ptr;
    ptr = malloc(1024 * 1048576 * sizeof(char));
//    int array[100];
    int i;
    for (i = 0; i < 100; i++) {
        printf("%d: %d\n", i, *(ptr + i));
    }
    printf("\n%d\n", ptr);
    free(ptr);
    return 0;
}
