#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc != 2){
        printf("\33[?25l");
    } else {
        printf("\33[?25h");
    }
}