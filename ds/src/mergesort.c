#include "../include/mergesort.h"

void MergeSort(int arr[], int l, int r)
{
	int m = 0;
	
	if(l < r)
	{
		m = (l + r) / 2;
		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);
		Merge(arr, l, m, r);	
	}
}

void Merge(int arr[], int l, int m, int r)
{
	int i = 0, j = 0, k = 0;
	int n1 = m - l + 1;
	int n2 = r - m;
	int *l_arr = (int *)malloc(sizeof(int) * n1);
	int *r_arr = (int *)malloc(sizeof(int) * n2);
	
	for(i = 0; i < n1; ++i)
	{
		l_arr[i] = arr[l + i];
	}
	for(j = 0; j < n2; ++j)
	{
		r_arr[j] = arr[m + j + 1];
	}
	
	i = 0;
	j = 0;
	k = l;
	
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
