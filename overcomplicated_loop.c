#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static jmp_buf env;

int main (void)
{
    srand(time(NULL));
    int a = 0;
    while (a == 0) {
        a += rand() * time(NULL);
        float c = 1 / a;

        for (int b = 20; !setjmp(env); b -= 21) {
            if ((a / b) < 20)
                c *= c;

            if (c == a)
                longjmp(env, 0);
            /*
             * Your code here.
             */
        }
    }
}
