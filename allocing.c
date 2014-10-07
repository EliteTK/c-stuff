/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
// Learning to malloc.
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[] ) {
    // malloc test
    char * string;
    string = (char *) malloc(10 * sizeof(char));

    *(string + 0) = 'a';
    *(string + 1) = 'b';
    *(string + 2) = 'c';
    *(string + 3) = '\n';
    *(string + 4) = '\0';

    printf("%s", string);

    free(string);
    string = NULL;
}
