// foursquare.c
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define Q ('Q'-'A')

typedef struct vec2 {
    int x;
    int y;
} Vec2;

int increinc(int *);
void allupper(char *);
void genkey(char *, char *);
Vec2 *newVec2(const int, const int);

int main(int argc, char **argv)
{
    int x, y, c=0;

    if(argc!=4){
        printf("Usage: %s <key1> <key2> <cipher>", *argv);
        exit(1);
    }

    printf("%s, %s ", *(argv+1), *(argv+2));

    char *trkey = *(argv+1);
    allupper(trkey);
    char *trfullkey = malloc(26);
    genkey(trkey, trfullkey);

    char *blkey = *(argv+2);
    allupper(blkey);
    char *blfullkey = malloc(26);
    genkey(blkey, blfullkey);

    char *cipher = *(argv+3);
    allupper(cipher);

    int i=0;
    Vec2 *trtable[25];
    for(x=0; x<5; x++)
        for(y=0; y<5; y++)
            trtable[trfullkey[i++]-'A'] = newVec2(x, y);
    free(trfullkey);

    i = 0;
    Vec2 *bltable[25];
    for(x=0; x<5; x++)
        for(y=0; y<5; y++)
            bltable[blfullkey[i++]-'A'] = newVec2(x, y);
    free(blfullkey);

    char basetable[5][5];
    for(x=0; x<5; x++)
        for(y=0; y<5; y++){
            if(c==Q)
                c++;
            basetable[x][y] = 'A' + c++;
        }

    for(i=0; i<strlen(cipher)/2; i++){
        char c1 = cipher[2*i];
        char c2 = cipher[2*i+1];

        putchar(basetable[trtable[c1-'A']->x][bltable[c2-'A']->y]);
        putchar(basetable[bltable[c2-'A']->x][trtable[c1-'A']->y]);
    }
    putchar('\n');

    for(i=0; i++; i<25){
        free(trtable[i]);
        free(bltable[i]);
    }

    return 0;
}

int increinc(int *num)
{
    (*num)++;
    return (*num)++;
}

void allupper(char *input)
{
    int i;
    for(i=0; i<strlen(input); i++)
        if(isalpha(input[i]))
            input[i]=toupper(input[i]);
}

void genkey(char *input, char *output)
{
    int dict[26];
    memset(dict, 0, 26*sizeof(int));

    int i, outpt = 0;
    for(i=0; i<strlen(input); i++){
        if(!dict[input[i]-'A']){
            output[outpt++]=input[i];
        }
        dict[input[i]-'A'] += 1;
    }

    for(i=0; i<26; i++)
        if(!dict[i] && i!=Q)
            output[outpt++]=i+'A';
    output[outpt]='\0';
}

Vec2 *newVec2(const int x, const int y)
{
    Vec2 *v = malloc(sizeof(Vec2));
    v->x = x;
    v->y = y;
    return v;
}
