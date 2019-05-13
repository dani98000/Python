#include <stdio.h>/*printf*/
#include <stdlib.h>

int soldiers2(int *soldiers_array, int num_of_soldiers);
int main()
{
	int number_of_soldiers=100;
	int *arr = (int *)malloc(sizeof(int) * number_of_soldiers); 
	printf("the last standing soldier is in the %d position\n", soldiers2(arr,number_of_soldiers));
	free(arr);
	
	return 0;
}

int soldiers2(int *soldiers_array, int num_of_soldiers)
{
	int i,temp;
	
	for(i=0; i<num_of_soldiers-1; i++)
	{
		soldiers_array[i] = i+1;
	}
	
	soldiers_array[i] = 0;
    i = 0;
    
	while(soldiers_array[i] != soldiers_array[soldiers_array[i]])
	{
		temp = soldiers_array[soldiers_array[i]];
		soldiers_array[soldiers_array[i]] = -1;
		soldiers_array[i] = temp;		
		i = soldiers_array[i];
	}
	
	return(i+1);
}


