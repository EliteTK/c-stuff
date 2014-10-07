/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 *
 *
 * This is a brainfuck to C parser. It outputs files that can be directly compiled by a
 * C compiler.
 *
 * WARNING: THIS PROGRAM PRODUCES CODE THAT ALLOWS UNRESTRICTED MEMORY ACCESS.
 * USE AT YOUR OWN RISK!!!!!!!!!!!!
 * This program takes input from stdin and outputs on stdout and stderr (for errors)
 */

#include<stdio.h>

#define rightAngle "++ptr;\n" // right angle bracket
#define leftAngle "--ptr;\n" // left angle bracket
#define plus "++*ptr;\n" // plus
#define minus "--*ptr;\n" // minus
#define period "putchar(*ptr);\n" // period
#define comma "*ptr = getchar();\n" // comma
#define leftSquare "while (*ptr) {\n" // left square bracket
#define rightSquare "}\n" // right square bracket

#define indent "    "

void autoIndent(int);

int main( int argc, char *argv[] ) {
    int indentLevel = 1;
    printf("// Generated with TK's \"fuck\" brainfuck to C parser.\n");
    printf("#include<stdio.h>\n");
    printf("#include<stdlib.h>\n");
    printf("\n");
    printf("int main() {\n");
    printf("    char *ptrt;\n");
    printf("    ptrt = calloc(1000, sizeof(char));\n");
    printf("    char *ptr;\n");
    printf("    ptr = ptrt;\n");
    printf("    // The following is directly parsed\n");

    char c;
    while ( ( c = getchar() ) != EOF ) {
        switch (c) {
            case 62:
                autoIndent(indentLevel);
                printf(rightAngle);
                break;
            case 60:
                autoIndent(indentLevel);
                printf(leftAngle);
                break;
            case 43:
                autoIndent(indentLevel);
                printf(plus);
                break;
            case 45:
                autoIndent(indentLevel);
                printf(minus);
                break;
            case 46:
                autoIndent(indentLevel);
                printf(period);
                break;
            case 44:
                autoIndent(indentLevel);
                printf(comma);
                break;
            case 91:
                autoIndent(indentLevel);
                indentLevel++;
                printf(leftSquare);
                break;
            case 93:
                indentLevel--;
                autoIndent(indentLevel);
                printf(rightSquare);
                break;
        }
    }
    printf("    // Closing cleanup\n");
    printf("    free(ptrt);\n");
    printf("    putchar('\\n');\n");
    printf("    return 0;\n}\n");
    if (--indentLevel)
        fprintf( stderr, "Incorrect number of brackets. - Error parsing file.\n");
    return 0;
}

void autoIndent(int levels) {
    int i;
    for (i = 0; i < levels; i++)
        printf(indent);
}
