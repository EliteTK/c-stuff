#include <stdio.h>

int ack(m, n)
int m, n;
{
        int ans;
        if (m == 0) ans = n + 1;
        else if (n == 0) ans = ack(m - 1, 1);
        else ans = ack(m - 1, ack(m, n - 1));
        return (ans);
}

int main(argc, argv)
int argc; char **argv;
{
        int i, j;
        for (j = 0; i <= 5; i++)
                for (j = 0; j <= 5; j++)
                        printf("ackerman(%d, %d) is: %d\n", i, j, ack(i, j));
        return 0;
}
