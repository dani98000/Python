/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Yoav        		*
*								*
*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "pq.h" /* it_t */

struct pq
{
	srtl_t *list;
};


pq_t *PQCreate(pqpriority_f PriorityFunction)
{
	pq_t *pq = (pq_t *)malloc(sizeof(pq_t));
	if(NULL == pq)
	{
		free(pq);
		return NULL;
	}
	
	pq->list = SrtLCreate(PriorityFunction, NULL);
	if(NULL == pq->list)
	{
		free(pq);
		return NULL;
	}
	
	return pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	SrtLDestroy(pq->list);
	free(pq);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	if(SrtLInsert(pq->list , data) == SrtLEnd(pq->list))
	{
		return 1;
	}
	
	return 0;
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SrtLGetData(SrtLBegin(pq->list));
}

int PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	SrtLPopFront(pq->list);
	
	return 0;
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SrtLIsEmpty(pq->list);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SrtLSize(pq->list);
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

int PQErase(pq_t *pq, const void *key, pqcmp_f ShouldErase)
{
	size_t counter = 0;
	sit_t found = NULL;
	assert(NULL != pq);
	
	found = SrtLFind(SrtLBegin(pq->list), SrtLEnd(pq->list), ShouldErase, key, NULL);
	
	if(found != SrtLEnd(pq->list))
	{
		SrtLErase(found);
		
		return 0;
	}
	
	return 1;
}
