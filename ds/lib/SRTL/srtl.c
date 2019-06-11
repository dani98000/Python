/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Alex         	*
*								*
*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../../include/DLL/dll.h" /* it_t */
#include "../../include/SRTL/srtl.h" /* it_t */

struct srtl
{
	dll_t *list;
	cmp_f is_before;
	void *params;
};

srtl_t *SrtLCreate(cmp_f is_before, const void *params)
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

sit_t SrtLInsert(srtl_t *srtl, const void *data)
{
	sit_t where = NULL;
	assert(NULL != srtl);

	if(SrtLIsEmpty(srtl))
	{  
		return DLLPushFront(srtl->list, data);
	}	
	
	where = DLLFind((DLLBegin(srtl->list)), (DLLEnd(srtl->list)), srtl->is_before, srtl->params, (void *)data);
	
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

sit_t SrtLFind(sit_t from, sit_t to, scmp_f compare, const void *params, const void *key)
{
	return DLLFind(from, to, compare, (void *)params, (void *)key);
}

int SrtLForEach(sit_t from, sit_t to, sact_f action, void *params)
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
	assert(NULL != srtl);

	return DLLNext(iter);
}

sit_t SrtLPrev(const sit_t iter)
{
	return DLLPrev(iter);
}

void *SrtLGetData(const sit_t iter)
{
	return DLLGetData(iter);
}

int SrtLIsSame(const sit_t iter1, const sit_t iter2)
{
	return(IsSameIter(iter1, iter2));	
}

void SrtLMerge(srtl_t *dest, srtl_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	sit_t where = SrtLBegin(dest);
	sit_t from = SrtLBegin(src);
	sit_t to = from;
	sit_t end = SrtLEnd(src); 
	
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
