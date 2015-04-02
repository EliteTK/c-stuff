#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CTOI(c) ((c) - 'A')
#define ITOC(c) ((c) + 'A')

void preprocess(char *str);

int main(int argc, char **argv)
{
	char *key, *ciphertext, *decodepos, *decodeneg;
	long offset;
	size_t keylength, textlength;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s <key> <offset> <ciphertext>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	key = argv[1];
	offset = strtol(argv[2], NULL, 10);
	ciphertext = argv[3];

	preprocess(key);
	preprocess(ciphertext);

	keylength = strlen(key);
	textlength = strlen(ciphertext);

	decodepos = malloc(textlength + 1);
	decodeneg = malloc(textlength + 1);

	for (size_t i = 0; i < textlength; i++) {
		decodepos[i] = ITOC((CTOI(ciphertext[i]) + offset + CTOI(key[i % keylength])) % 26);
		decodeneg[i] = ITOC((CTOI(ciphertext[i]) + 52 - offset - CTOI(key[i % keylength])) % 26);
	}

	decodepos[textlength] = '\0';
	decodeneg[textlength] = '\0';

	printf("+ %s\n- %s\n", decodepos, decodeneg);

	free(decodepos);
	free(decodeneg);

	return EXIT_SUCCESS;
}

void preprocess(char *str)
{
	char *src = str, *dest = str;

	while (*src != '\0') {
		if (isalpha(*src))
			*(dest++) = toupper(*src);
		src++;
	}

	*dest = '\0';
}
