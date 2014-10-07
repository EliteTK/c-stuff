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
#include <string.h>

struct test {
    char *string;
    int length;
};

int main(int argc, char **argv)
{
    struct test t = {"Testing.", strlen("Testing.")};

    char strbuf[256];

    strncpy(strbuf, t.string, t.length + 1);
    printf("%s\n", strbuf);

    return 0;
}
