/*
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
// -*- compile-command: "make LDLIBS=-lncurses ncurses_windows" -*-
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define WIDTH 20
#define HEIGHT 10

int main(void)
{
	WINDOW *box;
	int c;

	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_RED);

	box = derwin(stdscr, 10, 10, 10, 10);

	bkgd(COLOR_PAIR(1));
	wbkgd(box, COLOR_PAIR(2));

	while ((c = getch()) != EOF) {
		if (c == KEY_RESIZE) {
			int x, y, width, height;

			erase();

			getmaxyx(stdscr, y, x);

			width = x < WIDTH ? x : WIDTH;
			height = y < HEIGHT ? y : HEIGHT;

			wresize(box, height, width);

			mvderwin(box, (y - height) / 2, (x - width) / 2);

			bkgd(COLOR_PAIR(1));

			wbkgd(box, COLOR_PAIR(2));

			box(box, 0, 0);

			refresh();
		}
	}

	return EXIT_SUCCESS;
}
