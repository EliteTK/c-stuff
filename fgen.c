#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
        if (argc != 4) {
                fprintf(stderr, "Usage: %s <sampling-frequency> <frequency> <duration> [amplitude]\n", argv[0]);
                exit(1);
        }

        long int sfreq = strtol(argv[1], NULL, 10);
        long double freq = strtod(argv[2], NULL);
        if (freq <= 0) freq = 1;
        long double duration = strtod(argv[3], NULL);
        long double amplitude = 127;

        if (argc == 5) {
                amplitude = strtol(argv[4], NULL, 10);
                if (amplitude > 127) amplitude = 127;
                else if (amplitude < 0) amplitude = 0;
        }

        long double wave_length = sfreq / freq;

        for (long int i = 0; i < duration / 1000 * sfreq; i++)
                putchar((char)((sinf(i / wave_length * M_PI_2 * 4) + 1) * amplitude));

        return 0;
}
