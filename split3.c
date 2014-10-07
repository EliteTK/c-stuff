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
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int *genccountdict(char *);
char *nodup(char *, int *);
char *nnodup(char *, int *);
char *dup(char *, int *);

int main(int argc, char **argv)
{
    int i;
    if(argc!=2)
        exit(1);

    char *string = *(argv+1);
    int *dict = genccountdict(string);

    for(i = 0; i < strlen(string); i++)
        string[i] = toupper(string[i]);

    printf("nodup: %s\n", nodup(string, dict));
    printf("nnodup: %s\n", nnodup(string, dict));
    printf("dup: %s\n", dup(string, dict));
    return 0;
}

int *genccountdict(char *input)
{
    int *dict = calloc(sizeof(int), 26);
    int i;
    for(i=0; i<strlen(input); i++)
        if(isalpha(input[i]))
            dict[toupper(input[i])-'A']++;
    return dict;
}

char *nodup(char *input)
{
    char *output = malloc(strlen(input)+1);
    int i, outpt = 0;

    for(i=0; i<strlen(input); i++){
        if(!dict[input[i]-'A']){
            output[outpt++]=input[i];
            dict[input[i]-'A'] = 1;
        }
    }
    output[outpt]='\0';
    return output;
}

char *nnodup(char *input, int *dict)
{
    char *output = malloc(strlen(input)+1);
    int i, outpt = 0;
    for(i=0; i<strlen(input); i++)
        if(dict[input[i]-'A']==1)
            output[outpt++]=input[i];
    output[outpt]='\0';
    return output;
}

char *dup(char *input, int *dict)
{
    char *output = malloc(strlen(input)+1);
    int i, outpt = 0;
    for(i=0; i<strlen(input); i++)
        if(dict[input[i]-'A']>1)
            output[outpt++]=input[i];
    output[outpt] = '\0';
    int ndict[26];
    memset(ndict, 0, 26*sizeof(int));
    return nodup(output, ndict);
}
