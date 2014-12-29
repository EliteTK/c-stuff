/*
 * Countdown timer
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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

unsigned long int get_seconds(char *);

void usage(char *cmd)
{
	printf("Usage:\n"
		   "\t%s <n>{s,m,h,D,M,Y} ...\n", cmd);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Not enough arguments.\n");
		usage(argv[0]);
		exit(1);
	}

	unsigned long int total_seconds = 0;

	for (int i = 1; i < argc; i++)
		total_seconds += get_seconds(argv[i]);

	printf("Total time: %lu second(s).\nStarted at: %d\n", total_seconds, time(NULL));

	sleep(total_seconds);

	printf("Ended at: %d\n", time(NULL));

	while (1) {
		printf("Ring!\a\n");
		sleep(1);
	}

	return 0;
}

unsigned long int get_seconds(char *code)
{
	int length = strlen(code);
	if (length < 2) {
		return 0;
	}

	int multiplier = 0;
	char suffix = code[length - 1];
	switch (suffix) {
		case 's': multiplier = 1; break; // 1 second
		case 'm': multiplier = 60; break; // 1 minute
		case 'h': multiplier = 3600; break; // 1 hour
		case 'D': multiplier = 86400; break; // 1 day
		case 'M': multiplier = 2629746; break; // 30.4368 days
		case 'Y': multiplier = 31556940; break; // 365.242 days
		default : return 0;
	}

	char value[length + 1];
	strncpy(value, code, length + 1);

	value[length - 1] = '\0';

	return strtoul(value, NULL, 10) * multiplier;
}
