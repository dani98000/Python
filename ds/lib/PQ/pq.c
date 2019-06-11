
/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Alex         	*
*								*
*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../../include/PQ/pq.h" /* it_t */

struct pq
{
	srtl_t *list;
};

/*
typedef struct pq pq_t;
typedef int(*pqcmp_f)(const void *data, const void *key, const void *params);
*/

pq_t *PQCreate(pqcmp_f PriorityFunction)
{
	pq_t *pq = (pq_t *)malloc(sizeof(pq_t));
	if(NULL == pq)
	{
		free(pq);
		return NULL;
	}
	
	pq->list = SrtLCreate(PriorityFunction, NULL);
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
	SrtLInsert(pq->list , (const void *)data);
	return 1;
}
void *PQPeek(const pq_t *pq)
{
	return SrtLGetData(SrtLPrev(SrtLEnd(pq->list)));
}

int PQDequeue(pq_t *pq)
{
	SrtLPopBack(pq->list);
	return 1;
}

int PQIsEmpty(const pq_t *pq)
{
	return SrtLIsEmpty(pq->list);
}
size_t PQSize(const pq_t *pq)
{
	return SrtLSize(pq->list);
}
void PQClear(pq_t *pq)
{
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}
size_t PQErase(pq_t *pq, const void *key, pqcmp_f ShouldErase)
{
	size_t counter = 0;

	while (SrtLFind(SrtLBegin(pq->list), SrtLEnd(pq->list), ShouldErase, NULL, key) != SrtLEnd(pq->list))
	{
		SrtLErase(SrtLFind(SrtLBegin(pq->list), SrtLEnd(pq->list), ShouldErase, NULL, key));
		++counter;
	}
	return counter;
}
/* return number of deleted elements */
 
