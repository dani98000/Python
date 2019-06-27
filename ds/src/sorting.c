#include <stdlib.h> /* size_t */
#include <string.h>
#include <errno.h>
#include "../include/sorting.h"

/*
Compare  < 0 *left goes before *right
Compare == 0 *left is equivalent to *right
Compare  > 0 *left goes after *right
*/

/*void InsertionSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare);*/

void swap(void *x, void *y, size_t element_size)
{
	char *holder = (char *)malloc(element_size);

	if(NULL == holder)
	{
		perror("malloc failed");
	}	
	
	memcpy(holder, x, element_size);
	memcpy(x, y, element_size);
	memcpy(y, holder, element_size);
}

void BubbleSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare)
{
	char *left = (char *)base; 
	char *right = (char *)base + element_size;
	char *end = (char *)base + (n_elements - 1)*element_size;
	int i = 0, j = 0;
	int flag = 1;
	
	char *holder = (char *)malloc(element_size);
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
				swap(&left, &right, element_size);
				/*memcpy(holder, (void *)left, element_size);
				memcpy((void *)left, (void *)right, element_size);
				memcpy((void *)right, holder, element_size);*/
				
				
			}
			left += element_size;
			right += element_size;
		}
	}
	free(holder);
}

/*void SelectionSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare);*/

