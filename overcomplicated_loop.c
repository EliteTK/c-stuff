/*
 * ???
 *
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// I don't remember.

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static jmp_buf env;

int main (void)
{
    srand(time(NULL));
    int a = 0;
    while (a == 0) {
        a += rand() * time(NULL);
        float c = 1 / a;

        for (int b = 20; !setjmp(env); b -= 21) {
            if ((a / b) < 20)
                c *= c;

            if (c == a)
                longjmp(env, 0);
            /*
             * Your code here.
             */
        }
    }
}
