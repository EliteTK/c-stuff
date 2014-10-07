/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <stdio.h>
#include <stdlib.h>
#include <vecmat/vec.h>

int main(int argc, char **argv)
{
    Vec *v = vec_new(123, 12.1, 45);
    char *s = malloc(50);
    vec_tostring(s, v);
    printf(s);
}
