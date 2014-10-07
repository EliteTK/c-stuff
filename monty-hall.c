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
#include <stdlib.h>
#include <time.h>

#define ITERATIONS 1000

int main(int argc, char **argv)
{
    srand(time(NULL));

    int i, won = 0, lost = 0, opt, winopt, discard;
    for(i = 0; i<ITERATIONS; i++){
        opt = (float)rand() / (float)RAND_MAX * 3.0;
        winopt = (float)rand() / (float)RAND_MAX * 3.0;
        if(opt == winopt){
            discard = (float)rand() / (float)RAND_MAX * 2.0;
            if(!opt)
                discard +=1;
            else if(opt == 1 && discard)
                discard = 2;
        }else{
            discard = 3 - opt - winopt;
        }
        opt = 3 - opt - discard;

        if(opt == winopt)
            won++;
        else
            lost++;
    }

    printf("Won: %d, Lost: %d.\n", won, lost);
    return 0;
}
