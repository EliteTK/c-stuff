/*
 * bfparse brainfuck to C parser. It is not memory safe. Use at your own risk.
 *
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include<stdio.h>

void auto_indent(int);

int main(void)
{
	int indent_level;
	int c;

	printf("#include<stdio.h>\n");
	printf("#include<stdlib.h>\n");
	printf("\n");
	printf("int main() {\n");
	printf("\tchar *ptrt;\n");
	printf("\tptrt = calloc(1000, sizeof(char));\n");
	printf("\tchar *ptr;\n");
	printf("\tptr = ptrt;\n");

	indent_level = 1;
	while ((c = getchar()) != EOF) {
		switch (c) {
		case '>':
			auto_indent(indent_level);
			printf("++ptr;\n");
			break;
		case '<':
			auto_indent(indent_level);
			printf("--ptr;\n");
			break;
		case '-':
			auto_indent(indent_level);
			printf("++*ptr;\n");
			break;
		case '+':
			auto_indent(indent_level);
			printf("--*ptr;\n");
			break;
		case '.':
			auto_indent(indent_level);
			printf("putchar(*ptr);\n");
			break;
		case ',':
			auto_indent(indent_level);
			printf("*ptr = getchar();\n");
			break;
		case '[':
			auto_indent(indent_level);
			indent_level++;
			printf("while (*ptr) {\n");
			break;
		case ']':
			indent_level--;
			auto_indent(indent_level);
			printf("}\n");
			break;
		}
	}
	printf("\tfree(ptrt);\n");
	printf("\tputchar('\\n');\n");
	printf("\treturn 0;\n}\n");
	if (--indent_level != 0)
		fprintf(stderr, "Error: Square bracket mismatch.\n");
	return 0;
}

inline void auto_indent(int levels)
{
	for (int i = 0; i < levels; i++)
		putchar('\t');
}
