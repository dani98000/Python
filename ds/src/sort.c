/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 30/06/2019		*
*	 Reviewer: Ben           	*
*								*
*********************************/
#include <stdlib.h> /* size_t */
#include <string.h> /* memcpy */
#include <errno.h> /* errno */
#include <stdio.h> /* perror */
#include <assert.h> /* assert */

#include "../include/sort.h" /* sorting.h header */

size_t my_ktn(const void *value, const void *args);

typedef struct info
{
	key_to_num ktn;
	const void *args;
	size_t shift;
}info_t;

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
			Swap(left, right, element_size, holder);
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
				Swap(left, right, element_size, holder);
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
			if(Compare((const void *)min_index, (const void *)(char *)(unsorted_runner + element_size)) > 0)
			{
				min_index = unsorted_runner + element_size;
			}
			unsorted_runner += element_size;
		}
		Swap(min_index, sorted_runner, element_size, holder);
		sorted_runner += element_size;		
	}
	
	free(holder);
}

int CountingSort(void *base, size_t num_of_members, size_t element_size, key_to_num ktn, const void *args, size_t range)
{
	void *output = NULL;
	int *count = NULL;
	char *runner_base = base;
	char *runner_output = NULL;
	int i = 0;
	size_t index = 0;
	
	assert(NULL != base);
	
	output = (void *)malloc(num_of_members * element_size);
	if (NULL == output)
	{
		return -1;	
	}
	runner_output = output;
	
	count = (int *)calloc(range, sizeof(int));
	if (NULL == output)
	{
		return -1;	
	}
	
	for(i = 0; i < (signed)num_of_members; ++i)
	{
		index = ktn((runner_base + i * element_size), args);
		count[index] += 1;
	}
	
	for(i = 1; i < (signed)range; ++i)
	{
		count[i] += count[i - 1];
	}
	
	for(i = num_of_members - 1; i >= 0; --i)
    { 
    	index = ktn((runner_base + i * element_size), args); 
        memcpy(runner_output + (count[index] - 1) * element_size, runner_base + i * element_size, element_size);
        count[index] -= 1; 
    } 
    
	memcpy(base, output, element_size * num_of_members);
	free(output);
	
    return 0;
}

int RadixSort(void *base, size_t num_of_members, size_t element_size, key_to_num ktn, const void *args, size_t num_of_bytes)
{
	int count_nibs = 0;
	int pos = 0;
	info_t *info = NULL;

	assert(NULL != base);
	
	info = (info_t *)malloc(sizeof(info_t));
	if (NULL == info)
	{
		return -1;
	}
	
	info->args = args;
	info->ktn = ktn;
	info->shift = pos * count_nibs;
	
	count_nibs = num_of_bytes * 2;
	
	while(pos < count_nibs)
	{
		CountingSort(base, num_of_members, element_size, my_ktn, (info_t *)info, 16);
		++pos;
		info->shift = pos * 4;
	}
	
	free(info);
	
	return 0;
}

size_t my_ktn(const void *value, const void *args)
{
	info_t *info = (info_t *)args;
	
	return ((info->ktn(value, info->args) >> info->shift) & 0x0F);
}

static void Swap(void *x, void *y, size_t element_size, char *holder)
{	
	memcpy(holder, x, element_size);
	memcpy(x, y, element_size);
	memcpy(y, holder, element_size);
}
