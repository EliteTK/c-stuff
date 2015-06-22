#include <ncurses.h>
#include <stdio.h>

int getch_nodelay(void)
{
	int retval;

	nodelay(stdscr, TRUE);
	retval = getch();
	nodelay(stdscr, FALSE);

	return retval;
}

int main(void)
{
	cbreak();
	initscr();
	noecho();
	nonl();

	keypad(stdscr, TRUE);

	while (1) {
		char number[32];
		int c[5] = {
			getch(),
			getch_nodelay(),
			getch_nodelay(),
			getch_nodelay(),
			getch_nodelay()
		};

		if (c[1] == ERR)
			snprintf(number, 32, "%d ", c[0]);
		else if (c[2] == ERR)
			snprintf(number, 32, "%d-%d ", c[0], c[1]);
		else if (c[3] == ERR)
			snprintf(number, 32, "%d-%d-%d ", c[0], c[1], c[2]);
		else if (c[4] == ERR)
			snprintf(number, 32, "%d-%d-%d-%d ", c[0], c[1], c[2],
					c[3]);
		else if (c[5] == ERR)
			snprintf(number, 32, "%d-%d-%d-%d-%d ", c[0], c[1],
					c[2], c[3], c[4]);

		addstr(number);
	}

	return 0;
}
