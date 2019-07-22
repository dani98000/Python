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
#include <math.h> /* sqrt */

#include "sort.h" /* sorting.h header */

static size_t my_ktn(const void *value, const void *args);
static void Heapify(int *arr, int n_elements, int index, enum direction direction);
static int GetPartition(int arr[], int start,int end, enum direction direction);
static int Partition(int arr[], int start,int end, enum direction direction);
static void IntSwap(int *x, int *y);
static int RecurBinarySearch(const int arr[], int key, size_t left, size_t right, size_t *index);
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

int MergeSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare)
{
	size_t n1 = n_elements / 2;
	size_t n2 = n_elements - n1;

	char *b1 = base;
	char *b2 = (char *)base + (n1 * element_size);
	void *temp_arr = (void *)malloc(element_size * n_elements);
	char *tmp = temp_arr;
	
	if(n_elements <= 1)
	{
		free(temp_arr);

		return 0;     /* Already sorted */
	}
	if(temp_arr == NULL)
	{
		free(temp_arr);

		return - 1;
	}

	MergeSort(b1, n1, element_size, Compare);
	MergeSort(b2, n2, element_size, Compare);



	while (n1 > 0 && n2 > 0)
	{
		if ((Compare)(b1, b2) <= 0)
		{
			memcpy(tmp, b1, element_size);
			tmp += element_size;
			b1 += element_size;
			--n1;
		}
		else
		{
			memcpy(tmp, b2, element_size);
			tmp += element_size;
			b2 += element_size;
			--n2;
		}
	}
	if (n1 > 0)
	{
		memcpy(tmp, b1, n1 * element_size);
	}
	else if (n2 > 0)
	{
		memcpy(tmp, b2, n2 * element_size);
	}
	
	memcpy(base, temp_arr, n_elements * element_size);

	free(temp_arr);
	
	return 0;
}

void HeapSort(int arr[], size_t n, enum direction direction)
{
	int i = 0;

	assert(arr);

	for(i = n / 2 - 1; i >= 0; --i)
	{
		Heapify(arr, n, i, direction);
	}
		for (i = n - 1; i >= 0; --i)
		{
			IntSwap(&arr[0], &arr[i]);
			Heapify(arr, i, 0, direction);			
		}
}

void QuickSort(int arr[], size_t n, enum direction direction)
{
	int start = 0;
	int end = n - 1;
	int pivot_loc = 0;

	assert(arr);

	if(start < end)
	{
		pivot_loc= GetPartition(arr,start,end, direction);
		QuickSort(arr + start,pivot_loc - start, direction);
		QuickSort(arr + pivot_loc,end - pivot_loc + 1, direction);
	}
}

int BinarySearch(const int arr[], int key, size_t n, size_t *index)
{		
	assert(arr);

	return RecurBinarySearch(arr, key, 0, n-1,index);
}

int JumpSearch(const int arr[], int key, size_t n, size_t *index)
{
	int step = sqrt(n);
	int left = 0;
	int right = 0;
	int i = 0;

	assert(arr);

	while(left < n && arr[right] <= key)
	{
		right = n - 1;

		if(arr[left] <= key && arr[right] >= key)
		{
			break;
		}

		left += step;
	}

	for(; i < right; ++i)
	{
		if(arr[i] == key)
		{
			*index = i;

			return 1;
		}
	}

	return 0;
}

static int RecurBinarySearch(const int arr[], int key, size_t left, size_t right, size_t *index)
{
	int mid = 0;

	if(right >= left)
	{
		mid = left + (right - left) / 2;

		if(arr[mid] == key)
		{
			*index = mid;

			return 1;
		}

		if(arr[mid] > key)
		{
			return RecurBinarySearch(arr, key,left, mid - 1, index);
		}

		if(arr[mid] < key)
		{
			return RecurBinarySearch(arr, key,mid + 1, right, index);	
		}
	}

	return 0;
}

static int GetPartition(int arr[], int start,int end, enum direction direction)
{
	int size = end - start + 1;
	int i = rand() % (size) + start;
	IntSwap(&arr[end], &arr[i]);

	return Partition(arr,start,end, direction);
}

static int Partition(int arr[], int start,int end, enum direction direction)
{
	int pivot,i,j,temp;
	pivot = arr[end]; 
	i= start-1;
	for(j = start; j<= end-1; ++j)
	{
		if((arr[j] <= pivot && direction == ASC) || (arr[j] >= pivot && direction == DSC)) 
		{
			i++;
			IntSwap(&arr[j], &arr[i]);
		}
	}
	IntSwap(&arr[end], &arr[i+1]);

	return i+1;
}

static void Heapify(int *arr, int n_elements, int index, enum direction direction)
{
	int largest = index;
	int l = 2 * index + 1;
	int r = 2 * index + 2;

	while(l < n_elements || r < n_elements)
	{
		l = 2 * index + 1;
		r = 2 * index + 2;
	
		if (l < n_elements && (arr[l] > arr[largest] && direction == ASC || 
							   arr[l] < arr[largest] && direction == DSC))
		{
			largest = l;
		}

		if (r < n_elements && (arr[r] > arr[largest] && direction == ASC || 
							   arr[r] < arr[largest] && direction == DSC))
		{
			largest = r;
		}

		if (largest != index)
		{
			IntSwap(&arr[index], &arr[largest]);
			index = largest;
		}
		else
		{
			break;
		}
	}
}

static void IntSwap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

static size_t my_ktn(const void *value, const void *args)
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
