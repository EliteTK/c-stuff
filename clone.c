#include<stdio.h>

int main ( int argc, char *argv[] ) {
    char *string = "#include<stdio.h>\n\nint main ( int argc, char *argv[] ) {\n    char *string = \"%n\";\n    printf(*string, *string);\n}\n"; 
    printf(string, string);
}
