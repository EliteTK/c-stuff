/*
 * Copyright (C) 2014 - 2016  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#define ACHAR_CNT 26

static noreturn void die(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	exit(EXIT_FAILURE);
}

static int aclamp(long val)
{
	while (val < 0)
		val += ACHAR_CNT;

	return val % ACHAR_CNT;
}

static int getrot(const char *str)
{
	long val;
	char *endptr;

	if (!*str)
		die("Invalid argument '%s'\n", str);

	errno = 0;
	val = strtol(str, &endptr, 10);
	if (errno)
		die("Invalid argument '%s': %s", str, strerror(errno));
	if (*endptr)
		die("Invalid argument '%s'\n", str);

	return aclamp(val);
}

static int chval(int c)
{
	switch (tolower(c)) {
	case 'a': return  0;
	case 'b': return  1;
	case 'c': return  2;
	case 'd': return  3;
	case 'e': return  4;
	case 'f': return  5;
	case 'g': return  6;
	case 'h': return  7;
	case 'i': return  8;
	case 'j': return  9;
	case 'k': return 10;
	case 'l': return 11;
	case 'm': return 12;
	case 'n': return 13;
	case 'o': return 14;
	case 'p': return 15;
	case 'q': return 16;
	case 'r': return 17;
	case 's': return 18;
	case 't': return 19;
	case 'u': return 20;
	case 'v': return 21;
	case 'w': return 22;
	case 'x': return 23;
	case 'y': return 24;
	case 'z': return 25;
	}

	return -1;
}

static int valch(int c, bool upper)
{
	static const char chars[] = "abcdefghijklmnopqrstuvwxyz";
	int ret;

	if (c < 0 || c > 25)
		return 0;

	ret = chars[aclamp(c)];

	if (upper)
		ret = toupper(ret);

	return ret;
}

static int rot(int c, int r)
{
	return valch(aclamp(chval(c) + r), isupper(c));
}

int main(int argc, char **argv)
{
	int r, c;

	if (argc != 2)
		die("Usage: %s <rotation>\n", argv[0]);

	r = getrot(argv[1]);

	while (c = getchar(), c != EOF) {
		if (isalpha(c))
			putchar(rot(c, r));
		else
			putchar(c);
	}

	return 0;
}
