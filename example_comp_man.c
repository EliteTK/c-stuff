#include <stdio.h>
#include <stdlib.h>
struct test{int number;char letter;char *string;};void printstruct(const struct test*);int main(int argc,char*argv[]){struct test cake;cake.number=5;cake.letter='a';cake.string="Magic";printstruct(&cake);return 0;}void printstruct(const struct test*testp){printf("Number: %d\nLetter: %c\nString: %s\n",testp->number,testp->letter,testp->string);return;}
