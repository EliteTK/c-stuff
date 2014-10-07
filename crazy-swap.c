/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// Don't try this at home.

static inline void swap(int *a, int *b)
{
        *a=*a^*b;
        *b=*b^*a;
        *a=*a^*b;
}

int main(int argc, char **argv)
{
        int i;
        for (i = 0; i < 999999999; i++) {
                int a = 2;
                int b = 123;
                swap(&a, &b);
        }
        return 0;
}
