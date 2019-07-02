#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <stdio.h> /* debug printf */

#include "../include/sort.h" /* Declerations and Definitions */

static int Swap(void *data1, void *data2, void *data_temp, size_t data_size)
{	
	memmove(data_temp, data1, data_size);
	memmove(data1, data2, data_size);
	memmove(data2, data_temp, data_size);

	return 0;
}

/* typedef int (*cmp_f)(const void *data1, const void *data2); */

void BubbleSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare)
{
	char *arr_base = (char *)base;
	char *current_element = NULL;
	char *next_element = NULL;
	int iterations = n_elements - 1;
	int i = 0;
	int j = 0;
	void *temp = NULL;

	temp = malloc(element_size);
	assert(NULL != temp);

	for (i = iterations; i > 0; --i)
	{
		current_element = arr_base;		

		for (j = 0; j < i; ++j)
		{
			next_element = current_element + element_size;
			if (Compare(current_element, next_element)	> 0)
			{
				Swap(current_element, next_element, temp, element_size);
			}

			current_element = next_element;
		}
	}

	free(temp);
}

void SelectionSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare)
{
	char *arr_base = (char *)base;
	char *leftmost_element = NULL; /* equivalent to "min_element" */
	char *current_element = NULL;
	size_t i = 0;
	size_t j = 0;	
	void *temp = NULL; /* for optimization purposes */

	temp = malloc(element_size);
	assert(NULL != temp);

	for (i = 0; i < n_elements; ++i)
	{
		leftmost_element = arr_base;
		current_element = leftmost_element + element_size;

		for (j = i + 1; j < n_elements; ++j)
		{
			if (Compare(leftmost_element, current_element) > 0)
			{
				leftmost_element = current_element;
			}
			
			current_element += element_size;
		}

		Swap(arr_base, leftmost_element, temp, element_size);
	
		arr_base += element_size;
	}

	free(temp);
}

void InsertionSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare)
{
	char *arr_base = (char *)base;
	char *current_compare_element = NULL;
	char *current_sorted_element = arr_base + element_size;
	size_t i = 0;
	int flag = 0;
	void *temp = NULL;

	temp = malloc(element_size);
	assert(NULL != temp);

	for (i = 0; i < n_elements - 1; ++i)
	{
		current_compare_element = arr_base;
		flag = 0;
		for (; current_compare_element < current_sorted_element && 0 >= flag;
			  current_compare_element += element_size)
		{
			flag = Compare(current_compare_element, current_sorted_element);
		}
		
		if (0 < flag)
		{
			current_compare_element -= element_size;
	
			memcpy(temp, current_sorted_element, element_size);
			memmove(current_compare_element + element_size, 
					current_compare_element,
					current_sorted_element - current_compare_element); 
			/* element advanced by one after comparison in loop, hence this source/dest choice*/
			memcpy(current_compare_element, temp, element_size);
		}

		current_sorted_element += element_size;
	}

	free(temp);
}

int CountingSort(void *base, size_t n_elements, size_t element_size,
					key_to_num Ktn, const void *args, size_t range)
{
	char *arr_runner = base;
	size_t *count_arr = NULL;
	char *sorted_arr = NULL;
	size_t i = 0;
	size_t temp_index = 0;
	
	count_arr = (size_t *)calloc(range ,sizeof(size_t));
	sorted_arr = (char *)malloc(element_size * n_elements);
	if (NULL == count_arr || NULL == sorted_arr)
	{
		return 1;
	}
	
	for (i = 0; i < n_elements; ++i)
	{
		++count_arr[Ktn(arr_runner, args)];
		arr_runner += element_size;
	}
	arr_runner = base;
	
	for (i = 0; i < range - 1; ++i)
	{
		count_arr[i+1] += count_arr[i];
	}
	
	for (i = 0; i < n_elements; ++i)
	{
		temp_index = --count_arr[Ktn(arr_runner, args)];
		memcpy(sorted_arr + temp_index * element_size, arr_runner, element_size);
		arr_runner += element_size;
	}
	
	memcpy(base, sorted_arr, n_elements * element_size);
	
	free(sorted_arr);
	free(count_arr);

	return 0;
}
			
