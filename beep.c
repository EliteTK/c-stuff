#include <stdio.h>

main () {
	int i = 1;
	while ((getchar() != 27) && (i != 50)) {
		printf("\a");
		i++;
	}
}
