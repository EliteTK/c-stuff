/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

// A failed attempt to make a quine.
#include<stdio.h>

int main ( int argc, char *argv[] ) {
    char *string = "#include<stdio.h>\n\nint main ( int argc, char *argv[] ) {\n    char *string = \"%n\";\n    printf(*string, *string);\n}\n"; 
    printf(string, string);
}
