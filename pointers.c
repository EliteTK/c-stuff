#include <stdio.h>

int main () 
{
	long *ptr; //memory pointer
	long i; //increment to be used as pointer address
	printf("0x%X \n",&main);
	ptr = &main;
	printf(" --ADDRESS- : VAL- \n");
	
	for(i = 0; i <= 9999; i++) //could probably be done without using i
	{
		printf(" 0x%X : 0x%08X \n", ptr, *ptr); //output
		ptr++;
	}
	
	return 0;
}
