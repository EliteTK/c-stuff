/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    initscr();
    raw();
    noecho();

    int row, col;
    getmaxyx(stdscr, row, col);

    int x = 0, y = 0;

    bool run = true;
    while (run) {
        char c = getch();
        switch (c) {
            case 'w': if (x > 0) x--; break;
            case 's': if (x < (row - 1)) x++; break;
            case 'a': if (y > 0) y--; break;
            case 'd': if (y < (col - 1)) y++; break;
            case 'x': run = false; break;
        }
        move(x, y);
    }

    endwin();
}
