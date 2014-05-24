#include <stdio.h>

#define EVLEN 24

int main(int argc, char **argv)
{
    int i, c[24], last[8], diff;
    while(1){
        while(1){
            for(i=0; i<EVLEN; i++)
                c[i] = getchar();

            putchar('\n');
            for(i=0; i<8; i++)
                if(c[8+i] != last[i]){
                    diff = 1;
                    last[i] = c[8+i];
                }

            if(diff){
                printf("---- EVENT ----\n");
                diff = 0;
            }

            for(i=0; i<EVLEN; i++)
                printf("%2x", c[i]);
        }
    }
    return 0;
}
