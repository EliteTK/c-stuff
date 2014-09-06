#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FROM 0
#define TO   9

int8_t randrange(int8_t from, int8_t to)
{
        int base_random = rand();
        if (RAND_MAX == base_random) return randrange(from, to);
        int range = to - from,
            remainder = RAND_MAX % range,
           bucket = RAND_MAX / range;
        if (base_random < RAND_MAX - remainder) {
                return from + base_random/bucket;
        } else {
                return randrange(from, to);
        }
}

int main(int argc, char **argv)
{
        srand(time(NULL));
        int r;
        uint16_t *amounts = calloc(sizeof(uint16_t), (TO - FROM + 1));
        for (int i = 0; i < 1000; i++)
                amounts[randrange(FROM, TO) - FROM]++;

        for (int i = 0; i < TO - FROM + 1; i++)
                printf("%d: %d\n", i, amounts[i]);

        return 0;
}
