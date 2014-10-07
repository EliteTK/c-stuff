/*
 * String letter case randomiser.
 *
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

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
