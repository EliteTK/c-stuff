/*
 * A rather useless tool specifically designed to work with foursquare.c
 *
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLIST 1000
#define MAXKEY 100

int main(int argc, char **argv)
{
    int c, i, ii, listsize;
    char *list[MAXLIST];
    char *word = malloc(MAXKEY+1);
    for(i=0; i<MAXLIST; i++)
        if(!getword(word, MAXKEY))
            break;
        else
            memcpy(list[i]=malloc(strlen(word)+1), word, strlen(word)+1);
    listsize = ++i;
    for(i=0; i<listsize; i++)
        for(ii=i+1; ii<listsize-1; ii++)
            printf("./justkeys %s %s\n", list[i], list[ii]);
}

int getword(char *output, int maxlength)
{
    int c, p=0;
    while((c=getchar())!=EOF && isalpha(c) && p<maxlength)
        output[p++] = (char)c;
    output[p] = '\0';
    return p;
}
