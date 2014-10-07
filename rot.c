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
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define mod(A) ((A)%26)

int main(int argc, char **argv)
{
    if(argc!=3)
        exit(1);
    char *string = *(argv+1);
    int i, rot = (int)strtol(*(argv+2), NULL, 10);
    for(i=0; i<strlen(string); i++)
        if(isalpha(string[i])){
            if(string[i]-'A'<26){ // Simple way to differentiate lower and upper case if all letters are known to be alpha.
                putchar(mod(string[i]-'A'+rot)+'A');
            }else{
                putchar(mod(string[i]-'a'+rot)+'a');
            }
        }else{
            putchar(string[i]);
        }
    putchar('\n');
    return 0;
}
