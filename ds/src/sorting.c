#include <stdlib.h> /* size_t */
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>

#include "../include/sorting.h"


static void Swap(void *x, void *y, size_t element_size, char *holder);

void InsertionSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare)
{
	char *right = NULL;
	char *left = NULL;
	char *end = NULL;
	char *runner = NULL;
	char *holder = NULL;
	
	assert(NULL != base);
	
	right = (char *)base + element_size;
	left = (char *)base;
	end = (char *)base + element_size * (n_elements);
	runner = (char *)base + element_size;
	
	holder = (char *)malloc(element_size);
	if(NULL == holder)
	{
		perror("malloc failed");
	}

	while(right < end)
	{
		if(Compare((const void *)left, (const void *)right) > 0)
		{
			break;
		}
		left += element_size;
		right += element_size;
	}
	
	while(right < end)
	{
		runner = right;
		while(Compare((const void *)left, (const void *)right) > 0 && right > (char *)base)
		{
			Swap(&left, &right, element_size, holder);
			left -= element_size;
			right -= element_size;			
		}
		right = runner + element_size;
		left = runner;	
	}
	
	free(holder);
}

void BubbleSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare)
{
	char *left = NULL; 
	char *right = NULL;
	char *holder = NULL;
	char *end = NULL;
	int flag = 1;
	
	assert(NULL != base);
	
	end = (char *)base + (n_elements - 1)*element_size;
	
	holder = (char *)malloc(element_size);
	if(NULL == holder)
	{
		perror("malloc failed");
	}
	
	while(flag == 1)
	{
		flag = 0;
		left = (char *)base;
		right = (char *)base + element_size;
		while(left < end)
		{
			if(Compare((const void *)left, (const void *)right) > 0)
			{
				flag = 1;
				Swap(&left, &right, element_size, holder);
			}
			left += element_size;
			right += element_size;
		}
	}
	
	free(holder);
}

void SelectionSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare)
{
	char *min_index = NULL;
	char *unsorted_runner = NULL;
	char *sorted_runner = NULL;
	char *end = NULL;
	char *holder = NULL;
	
	assert(NULL != base);

	sorted_runner = (char *)base;	
	end = (char *)base + (n_elements - 1)*element_size;
	
	holder = (char *)malloc(element_size);
	if(NULL == holder)
	{
		perror("malloc failed");
	}	
			
	while(sorted_runner < end)
	{
		min_index = sorted_runner;
		unsorted_runner = sorted_runner;
		while(unsorted_runner < end)
		{
			if(Compare((const void *)min_index, (const void *)(char *)(unsorted_runner + 					element_size)) > 0)
			{
				min_index = unsorted_runner + element_size;
			}
			unsorted_runner += element_size;
		}
		Swap(&min_index, &sorted_runner, element_size, holder);
		sorted_runner += element_size;		
	}
	free(holder);
}

static void Swap(void *x, void *y, size_t element_size, char *holder)
{	
	memcpy(holder, *(void **)x, element_size);
	memcpy(*(void **)x, *(void **)y, element_size);
	memcpy(*(void **)y, holder, element_size);
}
