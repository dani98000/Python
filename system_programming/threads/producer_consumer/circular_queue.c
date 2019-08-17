/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Inbar Madar     	*
*								*
*********************************/

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* size_t */
#include <assert.h> /* assert */

#include "circular_queue.h"

struct c_queue
{
	int *arr;
	int capacity;
	int head;
	int tail;
	int size;
};

c_queue_t *QueueCreate(int capacity)
{
	c_queue_t *queue = NULL;

	assert(capacity > 0);

	queue = (c_queue_t *)malloc(sizeof(*queue));
	if(NULL == queue)
	{
		return NULL;
	}

	queue->arr = (int *)malloc(capacity * sizeof(int));
	if(NULL == queue->arr)
	{
		free(queue);
		queue = NULL;

		return NULL;
	}

	queue->capacity = capacity;
	queue->head = 0;
	queue->tail = -1;
	queue->size = 0;

	return queue;
}

void QueueDestroy(c_queue_t *queue)
{
	free(queue->arr);
	queue->arr = NULL;
	free(queue);
	queue = NULL;
}

int QueueIsEmpty(const c_queue_t *queue)
{
	return (!queue->size);
}

int QueueIsFull(c_queue_t *queue)
{
	return (queue->size == queue->capacity);
}

int QueueSize(c_queue_t *queue)
{
	return (queue->size);
}

int QueuePeek(const c_queue_t *queue)
{
	if(QueueIsEmpty(queue))
	{
		printf("Nothing inside the queue");

		return -1;
	}

	return (queue->arr[queue->head]);
}

void QueueEnqueue(c_queue_t *queue, const int data)
{
	if(queue->size == queue->capacity)
	{
		printf("queue is full!");

		return;
	}

	queue->tail = (queue->tail + 1) % queue->capacity;
	queue->arr[queue->tail] = data;
	++queue->size;
}

int QueueDequeue(c_queue_t *queue)
{
	if(QueueIsEmpty(queue))
	{
		printf("QueueIsEmpty");

		return 1;
	}

	queue->head = (queue->head + 1) % queue->capacity;
	--queue->size;

	return 0;
}
