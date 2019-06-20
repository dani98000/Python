#include <stdio.h>
#include <stdlib.h> /*printf*/

int lastsoldier(int *soldiers_array, int number_of_soldiers);
int nextalive(int *soldiers_array, int number_of_soldiers, int index);

int main()
{
	int number_of_soldiers=100;
	int i;
	int *arr = (int *)malloc(sizeof(int) * number_of_soldiers); 
	for(i = 0; i < number_of_soldiers; i++)
	{
		*(arr + i) = 1;
	}
	printf("the last standing soldier is in the %d place",lastsoldier(arr, number_of_soldiers));
	free(arr);
	
	return 0;
}

int nextalive(int *soldiers_array, int number_of_soldiers, int index)
{
	index += 1;
	index = index % number_of_soldiers;
	
	while(0 == soldiers_array[index])
	{
		++index;
		index = index % number_of_soldiers;	
	}
	
	return index;
}

int lastsoldier(int *soldiers_array, int number_of_soldiers)
{
	int current_soldier = 0;
	int nextkill = 1;
	
	while(nextkill != current_soldier)
	{
		soldiers_array[nextkill] = 0;
		current_soldier = nextalive(soldiers_array, number_of_soldiers, current_soldier);
		nextkill = nextalive(soldiers_array, number_of_soldiers ,current_soldier);
	}
	
	return (current_soldier+1);
}
