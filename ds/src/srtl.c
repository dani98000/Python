/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Alex         	*
*								*
*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/srtl.h" /* it_t */

struct srtl
{
	dll_t *list;
	isbefore_f is_before;
	const void *params;
};

srtl_t *SrtLCreate(isbefore_f is_before, const void *params)
{
	srtl_t *srtl = (srtl_t *)malloc(sizeof(srtl_t));
	if(NULL == srtl)
	{
		free(srtl);
		return NULL;
	}
	
	srtl->list = DLLCreate();
	if (NULL == srtl->list)
	{
		free(srtl->list);
		return NULL;
	}
	srtl->is_before = is_before;
	srtl->params = (void *)params;
	
	return srtl;
}

void SrtLDestroy(srtl_t *srtl)
{
	assert(NULL != srtl);
	DLLDestroy(srtl->list);
	free(srtl);
}

size_t SrtLSize(const srtl_t *srtl)
{
	assert(NULL != srtl);
	
	return DLLSize(srtl->list);
}

int SrtLIsEmpty(const srtl_t *srtl)
{
	assert(NULL != srtl);

	return DLLIsEmpty(srtl->list);
}

sit_t SrtLInsert(srtl_t *srtl, void *data)
{
	sit_t where = NULL;
	assert(NULL != srtl);

	if(SrtLIsEmpty(srtl))
	{  
		return DLLPushFront(srtl->list, data);
	}	
	
	where = DLLFind((DLLBegin(srtl->list)), (DLLEnd(srtl->list)), srtl->is_before, (void *)data, srtl->params);
	
	return DLLInsert(srtl->list, DLLPrev(where), (void *)data);
}


sit_t SrtLErase(sit_t where)
{
	return(DLLErase(where));
}

void SrtLPopFront(srtl_t *srtl)
{
	assert(NULL != srtl);

	DLLErase(DLLBegin(srtl->list));
}

void SrtLPopBack(srtl_t *srtl)
{
	assert(NULL != srtl);

	DLLErase(DLLPrev(DLLEnd(srtl->list)));
}

sit_t SrtLFind(sit_t from, sit_t to, isbefore_f compare, const void *key, const void *params)
{
	assert(NULL != from);
	assert(NULL != to);

	return DLLFind(from, to, compare, (void *)key, (void *)params);
}

int SrtLForEach(sit_t from, sit_t to, sact_f action,const void *params)
{
	return DLLForEach(from, to, action, params);
}

sit_t SrtLBegin(const srtl_t *srtl)
{
	assert(NULL != srtl);

	return DLLBegin(srtl->list);
}

sit_t SrtLEnd(const srtl_t *srtl)
{
	assert(NULL != srtl);

	return DLLEnd(srtl->list);
}

sit_t SrtLNext(const sit_t iter)
{
	assert(NULL != iter);

	return DLLNext(iter);
}

sit_t SrtLPrev(const sit_t iter)
{
	assert(NULL != iter);

	return DLLPrev(iter);
}

void *SrtLGetData(const sit_t iter)
{
	assert(NULL != iter);

	return DLLGetData(iter);
}

int SrtLIsSame(const sit_t iter1, const sit_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);	

	return(DLLIsSameIter(iter1, iter2));	
}

void SrtLMerge(srtl_t *dest, srtl_t *src)
{
	sit_t where = NULL;
	sit_t from = NULL;
	sit_t to = NULL;
	sit_t end = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);

	where = SrtLBegin(dest);
	from = SrtLBegin(src);
	to = from;
	end = SrtLEnd(src); 
	
	while(to != end)
	{
		if(dest->is_before(SrtLGetData(where), SrtLGetData(from), NULL))
		{
			while(to != end && dest->is_before(SrtLGetData(where), SrtLGetData(to), NULL))
			{
				to = SrtLNext(to);
			}
			
			DLLSpliceBefore(where, from, to);
			from = to;
		}
		else
		{
			where = SrtLNext(where);
		}
		
		if(where == SrtLEnd(dest))
		{
			to = end;
			DLLSpliceBefore(where, from, to);
		}	
	}
}
