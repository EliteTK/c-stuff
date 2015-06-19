#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TICKS 8000

int main(int argc, char **argv)
{
	uint64_t divs[] = {1, 2, 4, 5, 8, 10, 16, 20, 25, 32, 40, 50, 64, 80, 100, 125, 160, 200, 250, 320, 400, 500, 800, 1000, 1600, 2000, 4000, 8000};

	/*putchar('\n');*/

	/*for (uint64_t div = 0; div < 28; div++) {*/
		/*float frequency = 8000.0 / (float)divs[div];*/
		/*fprintf(stderr, "\r                                         ");*/
		/*fprintf(stderr, "\rFrequency: %f, Divs: %ld", frequency, divs[div]);*/
		/*fflush(stderr);*/
		/*for (uint64_t i = 0; i < 8000; i++)*/
			/*putchar(255 * !!((i / divs[div]) & 1));*/
	/*}*/

/*#define CYCLES 10*/
/*#define UNDER 10*/

	/*for (unsigned cycle = 0; cycle < 10000; cycle++) {*/
		/*float duty = (sinf((float)cycle / UNDER * M_PI) + 1) / (float)2;*/
		/*unsigned on_amount = duty * CYCLES;*/
		/*unsigned off_amount = CYCLES - on_amount;*/

		/*fprintf(stderr, "Cycle: %d, Duty: %f, On: %d, Off: %d\n", cycle, duty, on_amount, off_amount);*/

		/*for (unsigned i = 0; i < on_amount; i++)*/
			/*putchar(255);*/

		/*for (unsigned i = 0; i < off_amount; i++)*/
			/*putchar(0);*/
	/*}*/

	if (argc != 3)
		exit(EXIT_FAILURE);

	unsigned halfwidth = strtol(argv[1], NULL, 10);
	unsigned cycles = strtol(argv[2], NULL, 10);

	for (unsigned cycle = 0; cycle < cycles; cycle++) {
		for (unsigned i = 0; i < halfwidth; i++)
			putchar(255);
		for (unsigned i = 0; i < halfwidth; i++)
			putchar(0);
	}

	return 0;
}

/* link:-lm: */
