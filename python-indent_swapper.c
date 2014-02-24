// I don't remember ever writing this. I think this is copied straight from K&R.

#include<stdio.h>
#include<stdlib.h>

#define MAXFILE 1000
#define MAXLINE 1000

int readline(char *line, int maxline);
int stripspace(char *line);

int main(int argc, char *argv[]) {

	char line[MAXFILE][MAXLINE];
	int inspace, outspace, i, linecount, space;

	if (argc == 3) {
/*		inspace = atoi(argv[1]);
		outspace = atoi(argv[2]); */

        inspace = 4;
        outspace = 2;

        i = linecount = 0;

        while ( readline(line[i++], MAXLINE ) >= 0)
            linecount++;

/*      for (i = 0; i < linecount; i++) {
            space = stripspace(line[i]);
            space = space - space % inspace;
            space = space / inspace * outspace;
            addspace(line[i], space); 
        } */

	} else {
		return 1;
	}

	return 0;

}

int readline(char *string, int lim) {
	
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		string[i++] = c;

	if (c == '\n')
		string[i++] = c;

    if (c == EOF)
        i = -1;

	string[i] = '\0';
	return i;
}

int stripspace(char *string) {

	int i, ii;

	i = ii = 0;
	while (string[i] == ' ')
		i++;

	while ( (string[ii++] = string[i++]) != '\0')
		;

	return i - ii;
}

int addspace(char *string, int amount) {

    int i, ii;

    i = 0;
    while ( string[i++] != '\0' )
        ;

    ii = i + amount;

    while (--i != -1) {
        --ii;

        string [ii] = string [i];
    }

    while (--ii != -1)
        string [ii] = ' ';
}
