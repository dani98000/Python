#include <stdio.h>

int MaxSubArray(int *arr, int size, int *from, int *to)
{
	int i = 0;
	int max_sum = 0;
	int current_sum = 0;
	int counter = 0;
	int offset = 0;
	
	for(; i< size; ++i)
	{
		current_sum += arr[i];
		
		if(current_sum < 0)
		{
			current_sum = 0;
			counter = 0; 
		}
		else
		{
			++counter;
		}
		
		if(current_sum > max_sum)
		{
			*to = i;
			max_sum = current_sum;
			offset = counter;
		}
	
		*from = *to - offset + 1;
	}
	
	if(max_sum == 0)
	{
		i = 0;
		max_sum = arr[i]; 
		
		for(; i< size; ++i)
		{
			if(arr[i] > max_sum)
			{
				*from = i;
				*to = *from;
				max_sum = arr[i];
			}	
		}
	}
	
	return max_sum;
}

int main()
{
	int a = 0, b = 0;
	int arr[] = {-2, 1,-3, 4, -1, 2, 1, -5, 4};
	int arr2[] = {-2, -1, -3, -4, -1, -2, -1, -5, -4};	
	printf("max sum: %d\n", MaxSubArray(arr, 9, &a, &b));
	printf("from: %d\n", a);
	printf("to: %d\n", b);
	printf("max sum: %d\n", MaxSubArray(arr2, 9, &a, &b));
	printf("from: %d\n", a);
	printf("to: %d\n", b);	

	return 0;
}
