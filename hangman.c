/*
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_CHARS 26
#define MAX_GUESS 5

enum state {
	NONE,
	WIN,
	LOSS
};

int main(int argc, char **argv)
{
	bool guessed[ALPHABET_CHARS] = {0}, in_secret[ALPHABET_CHARS] = {0};
	char *secret;
	int bad_guesses = 0, c;
	size_t dest, length;
	enum state state = NONE;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <word>\n", argv[0]);
		return EXIT_FAILURE;
	}

	secret = argv[1];
	dest = 0;
	length = strlen(secret);
	for (size_t i = 0; i < length; i++)
		if (isalpha(secret[i]) || isspace(secret[i]))
			secret[dest++] = toupper(secret[i]);

	length = dest;
	for (size_t i = 0; i < length; i++)
		if (isalpha(secret[i]))
			in_secret[secret[i] - 'A'] = true;

	printf("Hangman\n=======\n\n");
	for (size_t i = 0; i < length; i++)
		if (isalpha(secret[i]) && !guessed[secret[i] - 'A'])
			putchar('_');
		else
			putchar(secret[i]);
	putchar('\n');

	while ((c = getchar()) != EOF) {
		if (!isalpha(c))
			continue;

		c = toupper(c);

		if (guessed[c - 'A'])
			goto print_state;

		if (!in_secret[c - 'A']) {
			bad_guesses++;
			printf("Wrong!\n");
			goto print_state;
		}

		guessed[c - 'A'] = true;

		for (unsigned i = 0; i < ALPHABET_CHARS; i++)
			if (in_secret[i] && !guessed[i])
				goto print_state;

		state = WIN;

		break;
print_state:
		for (size_t i = 0; i < length; i++)
			if (isalpha(secret[i]) && !guessed[secret[i] - 'A'])
				putchar('_');
			else
				putchar(secret[i]);
		putchar('\n');
		printf("You have %d guesses left.\n", MAX_GUESS - bad_guesses);

		if (bad_guesses >= MAX_GUESS) {
			state = LOSS;
			break;
		}
	}

	switch (state) {
	case WIN:
		printf("You won.\n");
		break;
	case LOSS:
		printf("You lost, the secret word was: %s\n", secret);
		break;
	case NONE:
		printf("Something weird happened.\n");
		break;
	}
}
