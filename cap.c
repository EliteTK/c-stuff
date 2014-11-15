/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char *capitalise(char *string)
{
	size_t length = strlen(string);
	bool last_sep = true; /* Nothing is a separator too. */
	for (unsigned i = 0; i < length; i++) {
		if (isalpha(string[i])) {
			string[i] = last_sep ? toupper(string[i]) : tolower(string[i]);
			last_sep = false;
		} else
			last_sep = true;
	}
	return string;
}

int main(void)
{
	char string[] = "thIs iS MEANT to Be some Kind OF tEsT strinG?\n";
	printf(capitalise(string));
	return true;
}
