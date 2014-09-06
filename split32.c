#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *nodup(char *, int *);
char *nnodup(char *, int *);
char *dup(char *, int *);

int main(int argc, char **argv)
{
    int i;
    if(argc!=2)
        exit(1);

    char *string = *(argv+1);
    int dict[26];
    memset(dict, 0, 26*sizeof(int));

    for(i = 0; i < strlen(string); i++)
        string[i] = toupper(string[i]);

    printf("nodup: %s\n", nodup(string, dict));
    printf("nnodup: %s\n", nnodup(string, dict));
    printf("dup: %s\n", dup(string, dict));

    int ii;

    for(i=0; i<26; i++){
        putchar('A'+i);
        for(ii=0; ii<dict[i]; ii++)
            putchar('=');
        putchar('\n');
    }
    return 0;
}

char *nodup(char *input, int *dict)
{
    char *output = malloc(strlen(input)+1);
    int i, outpt = 0;
    for(i=0; i<strlen(input); i++){
        if(!dict[input[i]-'A']){
            output[outpt++]=input[i];
        }
        dict[input[i]-'A'] += 1;
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
