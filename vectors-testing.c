#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define V_NEW(l) v_new(l, (double[])

typedef struct {
        int length;
        double *raw;
} Vec;

double v_dot(Vec *, Vec *);
Vec *v_new(int, double *);

int main(int argc, char **argv)
{
        Vec *v1 = v_new(3, (double[]){1, 2, 2});
        Vec *v2 = V_NEW(3){1, 2, 3});
        printf("Dot: %f\n", v_dot(v1, v2));
        printf("%d: %f, %f, %f.\n", v1->length, v1->raw[0], v1->raw[1], v1->raw[2]);
        printf("%d: %f, %f, %f.\n", v2->length, v2->raw[0], v2->raw[1], v2->raw[2]);

        free(v1);
        free(v2);
}

Vec *v_new(int length, double *raw)
{
        Vec *vec = malloc(sizeof(Vec));
        vec->raw = malloc(length * sizeof(double));
        vec->length = length;
        memcpy(vec->raw, raw, length * sizeof(double));
        return vec;
}

double v_dot(Vec *v1, Vec *v2)
{
        int shortest = MIN(v1->length, v2->length);

        double dot = 0;

        for (int i = 0; i < shortest; i++)
                dot += v1->raw[i] * v2->raw[i];

        return dot;
}
