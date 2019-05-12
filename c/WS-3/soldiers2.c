#include <stdio.h>/*printf*/


int main()
{
	int soldiers[100];
	int size=(sizeof(soldiers)/sizeof(soldiers[0]));
	int i,temp;
	
	for(i=0; i<size-1; i++)
	{
		soldiers[i] = i+1;
	}
	soldiers[i] = 0;
    i = 0;
    
	while(soldiers[i] != soldiers[soldiers[i]])
	{
		temp = soldiers[soldiers[i]];
		soldiers[soldiers[i]] = -1;
		soldiers[i] = temp;		
		i = soldiers[i];
	}
	
	printf("the last standing soldier is in the %d position\n", i+1);
	
	return 0;
}


