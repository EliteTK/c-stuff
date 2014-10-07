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

int main(int argc, char **argv)
{
    if(argc != 2){
        printf("\33[?25l");
    } else {
        printf("\33[?25h");
    }
}
