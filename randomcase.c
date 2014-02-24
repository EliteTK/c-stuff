// Randomises the cases of letters. An IRC in joke from when I found out about the C+=
// project. (Letter equality)
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define MAXLINE 1000

void upper (char string[], int position) {
	
	if (string[position] < 'z' && string[position] > 'a' ) {
		string[position] -= 'a';
		string[position] += 'A';
	}
}

void lower (char string[], int position) {
	
	if (string[position] < 'Z' && string[position] > 'A' ) {
		string[position] -= 'A';
		string[position] += 'a';
	}
}



int main (int argc, char **argv) {
	srand(time(NULL));
	
	char input_string[MAXLINE];
	char c;
	int i = 0;

	while ((c = getchar()) != '\0') {
		input_string[i++] = c;
	}
	
	input_string[i] = '\0';	
	
	for (i = 0; i < MAXLINE; i++) {
		(rand() & 1) ? upper(input_string, i) : lower(input_string, i);
	}
	
	printf("Output: %s \n", input_string);
} 