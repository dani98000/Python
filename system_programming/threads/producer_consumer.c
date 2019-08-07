#include <pthread.h>/* threads */
#include <stdlib.h>/* malloc */ 
#include <unistd.h> /* sleep */
#include <stdio.h>/* printf */

#define BUFFER_SIZE 1000
#define NUM_VALUES 1000

volatile int g_is_full = 0;
int init_value = 1;

struct args
{
	int *arr;
	int arr_length;
};

volatile struct args args;

void *producer(void *data)
{
	int i = 0;
	int flag = 1;
	while(init_value <= NUM_VALUES)
	{	
		if(!g_is_full)
		{
			for(i = 0; i < BUFFER_SIZE; ++i)
			{
				args.arr[i] = init_value;
			}
			++init_value;
			g_is_full = 1;
		}
	}

	return NULL;
}

void *consumer(void *data)
{
	int flag = 1;
	int i = 0;
	int count = 0;
	
	while(init_value <= NUM_VALUES + 1)
	{
		if(g_is_full)
		{
			for(i = 0; i < BUFFER_SIZE; ++i)
			{
				count += args.arr[i];
			}
			printf("count: %d\n", count);
			count = 0;
			g_is_full = 0;
		}
	}
	return NULL;
}

int main()
{
	int *arr = (int *)calloc(sizeof(int), BUFFER_SIZE);
	pthread_t producer_thr;
	pthread_t consumer_thr;
	int ret = 0;
	args.arr = arr;
	args.arr_length = BUFFER_SIZE;

	ret = pthread_create(&producer_thr, NULL, producer, NULL);
	if(ret != 0) 
	{
		printf("error\n");
    }

    ret = pthread_create(&consumer_thr, NULL, consumer, NULL);
	if(ret != 0) 
	{
		printf("error\n");
    }

  	sleep(1);

  	return 0;
}