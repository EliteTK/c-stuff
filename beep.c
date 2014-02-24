// What is there to say? This beeps a bunch.
#include <stdio.h>

main () {
	int i = 1;
	while ((getchar() != 27) && (i != 50)) {
		printf("\a");
		i++;
	}
}
