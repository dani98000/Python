/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Eldad        	*
*								*
*********************************/
#include <pthread.h>/* threads */
#include <stdlib.h>/* malloc */ 
#include <unistd.h> /* sleep */
#include <stdio.h>/* printf */
#include <assert.h>


#define BUFFER_SIZE 1000
#define NUM_VALUES 1000

int init_value = 1;
int g_arr[BUFFER_SIZE] = {0};
int g_busy = 0;
int g_is_full = 0;

void Produce()
{		
	int i = 0;

	printf("Producing...\n");
	for(i = 0; i < BUFFER_SIZE; ++i)
	{
		g_arr[i] = init_value;	
	}
	g_is_full = 1;
	++init_value;
}

void Consume()
{
	int count = 0;
	int i = 0;

	printf("Consuming...\n");

	for(i = 0; i < BUFFER_SIZE; ++i)
	{
		count += g_arr[i];
	}
	g_is_full = 0;

	printf("count: %d\n", count);
}

void *producer(void *data)
{
	(void)data;

	while(init_value <= NUM_VALUES)
	{
		while(!__sync_bool_compare_and_swap(&g_busy,0,1))
		{
			;
		}

		if(!g_is_full)
		{
			Produce();
		}
		g_busy = 0;
	}

	return NULL;
}

void *consumer(void *data)
{
	(void)data;

	while(init_value <= NUM_VALUES)
	{
		while(!__sync_bool_compare_and_swap(&g_busy,0,1))
		{
			;
		}

		if(g_is_full)
		{
			Consume();
		}
		g_busy = 0;
	}

	return NULL;
}

int main()
{
	pthread_t producer_thr;
	pthread_t consumer_thr;
	int ret = 0;

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

    pthread_join(producer_thr, NULL);
	pthread_join(consumer_thr, NULL);

  	return 0;
}