/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// Yes, I got lazy. And timer.c wasn't a thing back then.

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
        sleep(1);
        printf("Start:\a\n");
        for (int i = 0; i < 45; i += 5) {
                sleep(300);
                printf("Check water levels.\a\n");
                if (i == 24) {
                        printf("Add stuff from plate.\n");
                }
        }

        printf("All done.\a\n");

        return 0;
}
