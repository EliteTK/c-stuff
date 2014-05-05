#include <stdio.h>
#include <stdlib.h>

#define B2BP "%d%d%d%d%d%d%d%d"
#define B2B(byte)  \
    (byte & 0x80 ? 1 : 0), \
    (byte & 0x40 ? 1 : 0), \
    (byte & 0x20 ? 1 : 0), \
    (byte & 0x10 ? 1 : 0), \
    (byte & 0x08 ? 1 : 0), \
    (byte & 0x04 ? 1 : 0), \
    (byte & 0x02 ? 1 : 0), \
    (byte & 0x01 ? 1 : 0)

int main(int argc, char **argv)
{
    signed char *c=malloc(3*sizeof(char)), i;
    while(1){
        for(i=0; i<3; i++)
            c[i] = getchar();
        printf("%2x %2x %2x ", (unsigned char)c[0], (unsigned char)c[1], (unsigned char)c[2]);
        printf(": "B2BP B2BP B2BP" ", B2B(c[0]), B2B(c[1]), B2B(c[2]));
        printf(": %d %d %d\n", (signed char)c[0], (signed char)c[1], (signed char)c[2]);
    }
    return 0;
}
