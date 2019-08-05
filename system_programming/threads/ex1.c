#include <pthread.h>/* threads */
#include <stdlib.h>/* malloc */ 
#include <unistd.h> /* sleep */
#include <stdio.h>/* printf */

#define NUM_THREADS 100000

struct args
{
	int index;
	int *arr;
};

int IsValid(int *arr, int arr_length)
{
	int i = 0;
	int result = 1;
	for(i = 0; i < arr_length; ++i)
	{
		if(arr[i] == i + 1)
		{
			result *= 1;
		}
		else
		{
			result *= 0;
			break;
		}
	}

	return result;
}

void *connection_handler(void *args)
{
	struct args *my_data;   
    my_data = (struct args *)args;
	my_data->arr[my_data->index] = my_data->index + 1;

	return NULL;
}

int main()
{
	pthread_t thr;
	size_t i = 0;
	int *arr = NULL;
	struct args *args = malloc(NUM_THREADS * sizeof(*args));
	int ret = 0, res = 0;
	void *status = NULL;
	int counter = 0;

	arr = (int *)calloc(sizeof(int), NUM_THREADS);
	if (NULL == arr)
	{
		return -1;
	}

	for(i = 0; i < NUM_THREADS; ++i) 
	{
		args[i].arr = arr;
		args[i].index = i;
		ret = pthread_create(&thr, NULL, connection_handler, args + i);

		if(ret != 0) 
		{
			pthread_join(thr, &status);
			--i;
            printf("counter = %d\n", ++counter);
      	}
	}

	res = IsValid(arr,NUM_THREADS);
	if(res == 1)
	{
		printf("Success!!!!\n");
	}
	else
	{
		printf("Fail!!!!!\n");
	}

	free(arr);
	free(args);

	return 0;
}