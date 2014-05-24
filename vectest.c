#include <stdio.h>
#include <stdlib.h>
#include <vecmat/vec.h>

int main(int argc, char **argv)
{
    Vec *v = vec_new(123, 12.1, 45);
    char *s = malloc(50);
    vec_tostring(s, v);
    printf(s);
}
