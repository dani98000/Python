/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer:              	*
*								*
*********************************/

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* size_t */
#include <assert.h> /* assert */

#include "../../include/QUEUE/queue.h"
#include "../../include/SLL/sll.h"

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
	SLLDestroy(queue->list);
	free(queue);
}

void QueueDequeue(queue_t *queue)
{
	SLLPopFront((queue->list));
}

int QueueEnqueue(queue_t *queue, const void *data)
{
	SLLPushBack(queue->list,data);
	if(SLLPushBack(queue->list,data) == SLLEnd(queue->list))
	{
		return 1;
	}
	return 0;
}

void *QueuePeek(const queue_t *queue)
{
	SLLGetData(SLLBegin(queue->list));
}

int QueueIsEmpty(const queue_t *queue)
{
	return(SLLIsEmpty(queue->list));

}

size_t QueueSize(const queue_t *queue)
{
	return(SLLSize(queue->list));
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	while(QueueIsEmpty(src))
	{
		QueueEnqueue(dest, QueuePeek(src));
		QueueDequeue(src);
	}
	return(dest);
}
