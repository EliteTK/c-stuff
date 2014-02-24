#include <stdio.h>

#define void rp(char output[])

main () {
	rp("Test");
	rp("Ok, this is no longer a test.");
	rp("TK throws his arms around you and squeezes you");
}

rp (char output[]) {
	printf(" [RPOUT] : %s \n", output);
}
