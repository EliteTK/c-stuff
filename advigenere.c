/*
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CTOI(c) ((c) - 'A')
#define ITOC(c) ((c) + 'A')

void preprocess(char *str);

int main(int argc, char **argv)
{
	char *key, *ciphertext, *decoded;
	size_t keylength, textlength;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <ciphertext> <key>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	ciphertext = argv[1];
	key = argv[2];

	preprocess(key);
	preprocess(ciphertext);

	keylength = strlen(key);
	textlength = strlen(ciphertext);

	decoded = malloc(textlength + 1);

	for (size_t i = 0; i < textlength; i++)
		decoded[i] = (CTOI(ciphertext[i]) + CTOI(key[i % keylength])) % 26;

	for (unsigned offset = 0; offset < 26; offset++) {
		printf("%.2u : ", offset);
		for (unsigned i = 0; i < textlength; i++)
			putchar(ITOC((decoded[i] + offset) % 26));
		putchar('\n');
	}

	free(decoded);

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
