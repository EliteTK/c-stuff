/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include<stdio.h>

int main(int argc, const char *argv[]) {
    char *ptr = &main;
    int i;
    for (i = 0;; i++) {
        putchar(*(ptr+i));
    }
    return 0;
}
