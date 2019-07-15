#include <stdlib.h>/* Free */

#include "../include/mergesort.h" /* Merge Sort header file */

static void Merge(int arr[], int left, int middle, int right);

void MergeSort(int arr[], int left, int right)
{
	int middle = 0;
	
	if(left < right)
	{
		middle = (left + right) / 2;
		MergeSort(arr, left, middle);
		MergeSort(arr, middle + 1, right);
		Merge(arr, left, middle, right);	
	}
}

static void Merge(int arr[], int left, int middle, int right)
{
	int i = 0, j = 0, k = 0;
	int n1 = middle - left + 1;
	int n2 = right - middle;
	int *l_arr = (int *)malloc(sizeof(int) * n1);
	int *r_arr = (int *)malloc(sizeof(int) * n2);
	
	for(i = 0; i < n1; ++i)
	{
		l_arr[i] = arr[left + i];
	}
	for(j = 0; j < n2; ++j)
	{
		r_arr[j] = arr[middle + j + 1];
	}
	
	i = 0;
	j = 0;
	k = left;
	
	while(i < n1 && j < n2)
	{
		if(l_arr[i] <= r_arr[j])
		{
			arr[k] = l_arr[i];
			++i;
		}
		else
		{
			arr[k] = r_arr[j];
			++j;
		}
		++k;
	}
	
	for(; i < n1; ++i)
	{
		arr[k] = l_arr[i];
		++k;
	}
	for(; j < n2; ++j)
	{
		arr[k] = r_arr[j];
		++k;
	}
	
	free(l_arr);
	free(r_arr);
}
