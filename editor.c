/*
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#define _GNU_SOURCE
#include <errno.h>
#include <error.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>

bool running = true;
size_t position = 0;

char *program = "#include <stdio.h>\n" \
		"\n" \
		"int main(void)\n" \
		"{\n" \
		"\tprintf(\"Hello World\\n\");\n" \
		"\n" \
		"\treturn 0;\n" \
		"}";

char *usage = "%sUsage:\n" \
	      "\t%s <filename>";

void print_screen(void)
{
	mvaddnstr(0, 0, program, position);
}

int getch_nodelay(void)
{
	int retval;

	nodelay(stdscr, TRUE);
	retval = getch();
	nodelay(stdscr, FALSE);

	return retval;
}


void poll_input(void)
{
	int c = getch();

	if (c == 27 && getch_nodelay() == ERR) {
		running = false;
		return;
	}

	if (program[position] == c)
		position++;
}

int main(int argc, char **argv)
{
	FILE *file;

	if (argc != 2)
		error(1, 0, usage, "Incorrect number of arguments\n",
		      program_invocation_name);

	cbreak();
	initscr();
	noecho();

	intrflush(stdscr, FALSE);

	print_screen();
	while (running) {
		poll_input();
		print_screen();
	}

	endwin();

	if (file = fopen(argv[1], "w"), file == NULL)
		error(1, errno, "Could not access %s", argv[1]);

	fwrite(program, 1, position, file);

	fclose(file);

	printf("Saved.\n");

	return 0;
}
