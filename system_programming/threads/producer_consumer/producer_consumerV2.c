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

#include "queue.h"
#include "sll.h"

#define QUEUE_SIZE 1000
#define NUM_VALUES 1000
#define NUM_CONSUMERS 5
#define NUM_PRODUCERS 5

queue_t *queue = NULL;
pthread_mutex_t lock; 

int g_busy = 0;
int g_is_full = 0;
int counter = 0;


void Produce()
{		
	int data = 5;

	printf("Producing...\n");
	QueueEnqueue(queue, &data);	
	++counter;
}

void Consume()
{
	int data = 0;

	printf("Consuming...\n");
	printf("queue size: %d\n", QueueSize(queue));

	data = *(int *)QueuePeek(queue);
	QueueDequeue(queue);
	--counter;

	printf("data: %d\n", data);
}

void *producer(void *data)
{
	(void)data;

	while(1)
	{
		sleep(1);

		/*Critical Section*/
		pthread_mutex_lock(&lock);
		{
			if(counter < 1000)
			{
				Produce();
			}
		}
		pthread_mutex_unlock(&lock);
	}

	return NULL;
}

void *consumer(void *data)
{
	(void)data;

	while(1)
	{
		/*Critical Section*/
		pthread_mutex_lock(&lock);
		{
			if(!QueueIsEmpty(queue))
			{
				Consume();
			}
		}
		pthread_mutex_unlock(&lock);
	}

	return NULL;

}

int main()
{
	pthread_t producer_thr;
	pthread_t consumer_thr;
	int ret = 0;
	int i = 0;
	pthread_t *consumers_id = (pthread_t *)malloc(sizeof(pthread_t) * NUM_CONSUMERS);
	pthread_t *producers_id = (pthread_t *)malloc(sizeof(pthread_t) * NUM_PRODUCERS);

	pthread_mutex_init(&lock, NULL);

	queue = QueueCreate();

	for(i = 0; i < NUM_PRODUCERS; ++i)
	{
		ret = pthread_create(&producers_id[i], NULL, producer, NULL);
		if(ret != 0) 
		{
			perror("error1: \n");
	    }
	}

	for(i = 0; i < NUM_CONSUMERS; ++i)
	{
		ret = pthread_create(&consumers_id[i], NULL, consumer, NULL);
		if(ret != 0) 
		{
			perror("error2: \n");
	    }
	}

    for(i = 0; i < NUM_PRODUCERS; ++i)
	{
		ret = pthread_join(producers_id[i], NULL);
		if(ret != 0) 
		{
			perror("error3: \n");
	    }
	}

    for(i = 0; i < NUM_CONSUMERS; ++i)
	{
		ret = pthread_join(consumers_id[i], NULL);
		if(ret != 0) 
		{
			perror("error4: \n");
	    }
	}

    pthread_mutex_destroy(&lock);

  	return 0;
}