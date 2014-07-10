#include <stdio.h>
#include <string.h>

struct test {
    char *string;
    int length;
};

int main(int argc, char **argv)
{
    struct test t = {"Testing.", strlen("Testing.")};

    char strbuf[256];

    strncpy(strbuf, t.string, t.length + 1);
    printf("%s\n", strbuf);

    return 0;
}
