#include <stdio.h>

void sort1(int arr[], int arr_length)
{
	int i = 0, j = 0, temp = 0;
	for(; j < arr_length - 1; j++)
	{
		i=0;	
		for(; i < arr_length - 1; i++)
		{
			if(arr[i] > arr[i + 1])
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
}

void finddup(int arr[], int arr_length)
{
	int i = 0, IsDup = 0;
	sort1(arr, arr_length);
	
	for(; i < arr_length - 1; i++)
	{
		if(arr[i] == arr[i + 1] && IsDup == 0)
		{
			IsDup = 1;
			printf("%d,",arr[i]);
		}
		else if(arr[i] != arr[i + 1])
		{
			IsDup = 0;
		}
	}
}

int main()
{
	int arr[] = {8, 0, 58, 100, 58, 58, 5, 1, 8, 13, 58, 0, 100};
	finddup(arr, 13);
	
	return 0;
}
