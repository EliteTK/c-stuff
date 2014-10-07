/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// Deja-vu?
#include<stdio.h>
#include<stdlib.h>

int main() {
    int *ptr;
    ptr = malloc(1024 * 1048576 * sizeof(char));
//    int array[100];
    int i;
    for (i = 0; i < 100; i++) {
        printf("%d: %d\n", i, *(ptr + i));
    }
    printf("\n%d\n", ptr);
    free(ptr);
    return 0;
}
