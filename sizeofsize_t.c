/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// Really self explanatory.
#include<stdio.h>
#include<stdlib.h>

int main ( int argc, char *argv[] ) {
    int size = sizeof(size_t);
    printf("The size of size_t is %dB or %db\n", size, size * 8);
}
