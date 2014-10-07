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
#include<stdlib.h>

int main(void) {
    printf("This is before the sleep.\n");
    sleep(10);
    printf("This is after the sleep and before the for loop.\n");
    long i;
    for(i = 0; i < 999999999999999; i++)
        ;
    printf("This is after the for loop.\n");
}
