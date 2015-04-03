/*
 * A Four Square cipher decoder. (Don't look directly at the mess)
 *
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Q ('Q'-'A')

#define CTOI(c) ((c) - 'A')
#define ITOC(c) ((c) + 'A')

struct vec2 {
	int x;
	int y;
};

int increinc(int *);
void preprocess(char *);
void genkey(char *, char *);
struct vec2 *newVec2(const int, const int);

int main(int argc, char **argv)
{
	int x, y, c = 0, i;
	char trfullkey[26], blfullkey[26], *trkey, *blkey, *cipher;
	struct vec2 trtable[25], bltable[25];

	if(argc!=4){
		printf("Usage: %s <key1> <key2> <cipher>", *argv);
		exit(1);
	}

	printf("%s, %s ", *(argv+1), *(argv+2));

	trkey = argv[1];
	preprocess(trkey);
	genkey(trkey, trfullkey);

	blkey = argv[2];
	preprocess(blkey);
	genkey(blkey, blfullkey);

	cipher = argv[3];
	preprocess(cipher);

	i = 0;
	for(x=0; x<5; x++)
		for(y=0; y<5; y++) {
			trtable[CTOI(trfullkey[i])].x = x;
			trtable[CTOI(trfullkey[i])].y = y;
			i++;
		}

	i = 0;
	for(x=0; x<5; x++)
		for(y=0; y<5; y++) {
			bltable[CTOI(blfullkey[i])].x = x;
			bltable[CTOI(blfullkey[i])].y = y;
			i++;
		}


	char basetable[5][5];
	for (x = 0; x < 5; x++)
		for (y = 0; y < 5; y++){
			if (c == Q)
				c++;
			basetable[x][y] = 'A' + c++;
		}

	for(size_t i = 0; i < strlen(cipher) / 2; i++){
		char c1 = cipher[2*i];
		char c2 = cipher[2*i+1];

		putchar(basetable[trtable[CTOI(c1)].x][bltable[CTOI(c2)].y]);
		putchar(basetable[bltable[CTOI(c2)].x][trtable[CTOI(c1)].y]);
	}
	putchar('\n');

	return EXIT_SUCCESS;
}

inline int increinc(int *num)
{
	(*num)++;
	return (*num)++;
}

void preprocess(char *str)
{
	char *src = str, *dest = str;

	while (*src != '\0') {
		if (isalpha(*src))
			*(dest++) = toupper(*src);
		src++;
	}

	*(++dest) = '\0';
}

void genkey(char *input, char *output)
{
	bool dict[26] = {0};
	int ii = 0;

	for (size_t i = 0; i < strlen(input); i++) {
		if (!dict[CTOI(input[i])]) {
			output[ii++] = input[i];
			dict[CTOI(input[i])] = true;
		}
	}

	for (unsigned i = 0; i < 26; i++)
		if (!dict[i] && i != Q)
			output[ii++] = ITOC(i);

	output[ii]='\0';
}
