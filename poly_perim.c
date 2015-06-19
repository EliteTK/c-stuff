#include <stdio.h>
#include <math.h>

double poly_perim(unsigned ndims, double *xcoords, double *ycoords)
{
	double retval = 0;

	for (unsigned i = 0; i < ndims; i++) {
		double left = xcoords[(i + 1) % ndims] - xcoords[i];
		double right = ycoords[(i + 1) % ndims] - ycoords[i];

		retval += sqrt(left * left + right * right);
	}

	return retval;
}

int main(void)
{
	printf("Perimiter: %f\n", poly_perim(3,
					     (double []){1, 1, 4},
					     (double []){2, 5, 5}));

	return 0;
}
