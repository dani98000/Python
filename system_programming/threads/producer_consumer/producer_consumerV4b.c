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
#include <semaphore.h>  

#include "circular_queue.h"

#define QUEUE_SIZE 1000
#define NUM_VALUES 1000
#define NUM_CONSUMERS 5
#define NUM_PRODUCERS 5

c_queue_t *queue = NULL;
pthread_mutex_t lock; 
pthread_mutex_t lock2; 

sem_t queue_counter;
sem_t max_counter;

int g_busy = 0;
int g_is_full = 0;
int counter = 0;


void Produce()
{		
	int data = 5;

	printf("Producing...\n");
	QueueEnqueue(queue, data);	
}

void Consume()
{
	int data = 0;

	printf("Consuming...\n");
	printf("queue size: %d\n", QueueSize(queue));

	data = QueuePeek(queue);
	QueueDequeue(queue);

	printf("data: %d\n", data);
}

void *producer(void *data)
{
	(void)data;

	while(1)
	{
		/*sleep(1);*/

		/*Critical Section*/	
		sem_wait(&max_counter);

		pthread_mutex_lock(&lock2);
		{
			Produce();
	    	sem_post (&queue_counter);  
		}
		pthread_mutex_unlock(&lock2);


	}

	return NULL;
}

void *consumer(void *data)
{
	(void)data;

	while(1)
	{
		/*Critical Section*/
		sem_wait(&queue_counter);

		pthread_mutex_lock(&lock);
		{
			Consume();
		    sem_post (&max_counter);  
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
	pthread_mutex_init(&lock2, NULL);

	
	sem_init(&queue_counter, 0, 0);
	sem_init(&max_counter, 0, QUEUE_SIZE);

	queue = QueueCreate(QUEUE_SIZE);

	for(i = 0; i < NUM_PRODUCERS; ++i)
	{
		ret = pthread_create(&producers_id[i], NULL, producer, NULL);
		if(ret != 0) 
		{
			perror("error: \n");
	    }
	}

	for(i = 0; i < NUM_CONSUMERS; ++i)
	{
		ret = pthread_create(&consumers_id[i], NULL, consumer, NULL);
		if(ret != 0) 
		{
			perror("error: \n");
	    }
	}

    for(i = 0; i < NUM_PRODUCERS; ++i)
	{
		ret = pthread_join(producers_id[i], NULL);
		if(ret != 0) 
		{
			perror("error: \n");
	    }
	}

    for(i = 0; i < NUM_CONSUMERS; ++i)
	{
		ret = pthread_join(consumers_id[i], NULL);
		if(ret != 0) 
		{
			perror("error: \n");
	    }
	}

    pthread_mutex_destroy(&lock);
    sem_destroy(&queue_counter); 
    QueueDestroy(queue);

  	return 0;
}