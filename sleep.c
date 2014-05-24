#include<stdio.h>
#include<stdlib.h>

int main(void) {
    printf("This is before the sleep.\n");
    sleep(10);
    printf("This is after the sleep and before the for loop.\n");
    long i;
    for(i = 0; i < 999999999999999; i++)
        ;
    printf("This is after the for loop.\n");
}
