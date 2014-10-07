/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// I don't know what this is.
#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv[]) {
    char **string;

    string = malloc(100)
    *string = "test";

    printf("%s", **string);
}
