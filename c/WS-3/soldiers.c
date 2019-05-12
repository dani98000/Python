#include <stdio.h>

int nextalive(int soldiers[],int arr_length, int index);
int main()
{


	int soldiers[8]={1,1,1,1,1,1,1,1};
	int size=(sizeof(soldiers)/sizeof(soldiers[0]));
	int current_soldier=0;
	int nextkill=1;
	while(nextkill != current_soldier)
	{
		soldiers[nextkill] = 0;
		current_soldier=nextalive(soldiers,size,current_soldier);
		nextkill=nextalive(soldiers,size,current_soldier);
	}
	printf("the last standing soldier is in the %d place",current_soldier+1);
	return 0;
}

int nextalive(int soldiers[],int arr_length, int index)
{
	index+=1;
	index=index%arr_length;
	while(soldiers[index] == 0)
	{
		++index;
		index=index%arr_length;	
	}
	return index;
}
