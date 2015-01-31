/*
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <linux/input.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	struct input_event *ie;
	FILE *evdev;

	if (argc != 2) {
		fprintf(stderr, "\aError: No evdev file.\n");
		exit(EXIT_FAILURE);
	}

	ie = malloc(sizeof(struct input_event));
	evdev = fopen(argv[1], "r");

	while (!feof(evdev)) {
		fread(ie, 1, sizeof(struct input_event), evdev);
		printf("Time: Sec: %d,\tUSec: %d,\tType: %d,\tCode: %d,\tValue: %d\n",
				ie->time.tv_sec, ie->time.tv_usec,
				ie->type, ie->code, ie->value);
	}

	return EXIT_SUCCESS;
}
