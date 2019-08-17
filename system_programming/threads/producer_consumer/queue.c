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

#include "sll.h"	   /*   Files   */
#include "queue.h"

struct queue
{
	sll_t *list;
};

queue_t *QueueCreate()
{
	queue_t *queue = (queue_t *)malloc(sizeof(struct queue));
	if(NULL == queue)
	{
		free(queue);
		return NULL;
	}
	
	queue->list = SLLCreate();
	
	return(queue);
}

void QueueDestroy(queue_t *queue)
{
	assert(queue != NULL);	
	
	SLLDestroy(queue->list);
	free(queue);
}

void QueueDequeue(queue_t *queue)
{
	assert(queue != NULL);
	assert(QueueSize(queue) > 0);
	
	SLLPopFront(queue->list);
}

int QueueEnqueue(queue_t *queue, const void *data)
{
	assert(queue != NULL);

	return!(SLLPushBack(queue->list,data) == SLLEnd(queue->list));
}

void *QueuePeek(const queue_t *queue)
{
	assert(queue != NULL);
	assert(QueueSize(queue)>=0);
	
	return (SLLGetData(SLLBegin(queue->list)));
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(queue != NULL);

	return(SLLIsEmpty(queue->list));
}

size_t QueueSize(const queue_t *queue)
{
	assert(queue != NULL);

	return(SLLSize(queue->list));
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	it_t current = SLLBegin(src->list);
	assert(dest != NULL);
	assert(src != NULL);
	
	while(SLLNext(current) !=NULL)
	{
		QueueEnqueue(dest, SLLGetData(current));
		current = SLLNext(current);
	}
	
	return(dest);
}
