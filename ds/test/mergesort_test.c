#include "../include/mergesort.h"

int main()
{
	int i = 0;
	int arr[] = {5,17,20,1,5,3,4,14,0,1,85,24,5,0};
	int arr_length = sizeof(arr) / sizeof(int);
	MergeSort(arr, 0, arr_length - 1);

	for(; i < arr_length; ++i)
	{
		printf("%d,", arr[i]);
	}
}
