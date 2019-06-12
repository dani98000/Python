/*******************************************
		AUTHOR: BEN IZAKSON
		REVIEW: DANIEL MAIZEL
		12.06.19
*******************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <ctype.h>  /* size_t */

#include "../../include/SRTL/srtl.h" 

#define USE89(x) (void) x
#define ISBF(x, y) isBefore(SrtLGetData(x) ,SrtLGetData(y), NULL)

struct srtl 
{
	dll_t *list;
	scmp_f is_before;
	const void *params;
};

/* SERVICE FUNCTIONS */
static scmp_f GetIsBefore(srtl_t *list);

/* FUNCTIONS*/
srtl_t *SrtLCreate (scmp_f IsBefore, const void *params)
{
	srtl_t *new_list = NULL;

	assert (NULL != IsBefore);
	
	new_list = (srtl_t *) malloc (sizeof(struct srtl)); 
	if(NULL == new_list)
	{
		return NULL;
	}
	
	new_list->list  = DLLCreate();
	if(NULL == new_list->list)
	{
		SrtLDestroy(new_list);
		return NULL;
	}
	
	new_list->is_before = IsBefore;
	new_list->params = params;
	
	return new_list; 
}

void SrtLDestroy (srtl_t *list)
{	
	assert(NULL != list);
	
	DLLDestroy(list->list);
	free(list);
}

size_t SrtLSize (const srtl_t *list)
{
	size_t count = 0;
	sit_t iterator = NULL; 
	sit_t stop = NULL; 
	
	assert(NULL != list);
	
	stop = SrtLEnd(list);
	iterator = SrtLBegin(list);
	
	while(stop != iterator)
	{	
		iterator = SrtLNext(iterator);
		++count;
	}
		
	return count;
}

int SrtLIsEmpty (const srtl_t *list)
{	
	assert(NULL != list);
		
	return SrtLBegin(list) == SrtLEnd(list);
}

sit_t SrtLInsert (srtl_t *list, void *data)
{
	sit_t holder = NULL;
	
	assert(NULL != list);
	
	holder = SrtLFind(SrtLBegin(list), SrtLEnd(list), GetIsBefore(list), data, NULL);
		
	return DLLInsert(list->list, SrtLPrev(holder) ,data);
}

sit_t SrtLErase (sit_t item)
{
	it_t result = NULL;
	
	assert(NULL != item);

	result = DLLNext(item);
	DLLErase(item);
	
	return result;
}

void SrtLPopFront (srtl_t *list)
{
	assert(NULL != list);
	
	DLLPopFront(list->list);
}

void SrtLPopBack(srtl_t *list)
{
	assert(NULL != list);

	DLLPopBack(list->list);
}

sit_t SrtLFind (sit_t from, sit_t to, scmp_f compare,const void *key, const void *params)
{	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != compare);
	assert(NULL != key);
	
	while(from != to && compare(SrtLGetData(from), key, params) == 0)
	{
		from = SrtLNext(from);
	}
	
	USE89(params);
	return from;
}

int SrtLForEach	(sit_t from, sit_t to, sact_f action,const  void *param)
{	
	int result = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action);
	
	while(from != to)
	{
		if (0 != (result = action(SrtLGetData(from), param) ) )
		{
			return result;
		}
		from = SrtLNext(from);
	}

	return 0;	
}

sit_t SrtLBegin (const srtl_t *list)
{	
	assert(NULL != list);
	
	return DLLBegin(list->list);
}

sit_t SrtLEnd (const srtl_t *list)
{
	assert(NULL != list);
	
	return DLLEnd(list->list);
}

sit_t SrtLNext (const sit_t item)
{
	assert(NULL != item);
	
	return DLLNext(item);
}

sit_t SrtLPrev (const sit_t item)
{
	assert(NULL != item);
	
	return DLLPrev(item);
}

void *SrtLGetData (const sit_t item)
{
	assert(NULL != item);
	
	return DLLGetData( item);
}

int SrtLIsSameIter (const sit_t item1,const sit_t item2)
{	
	return item1 == item2;
}

/* No merging empty lists. Has to have similar isBefore function */
void SrtLMerge (srtl_t *dest, srtl_t *src)
{
	sit_t where = SrtLBegin(dest);
	sit_t dest_end = SrtLEnd(dest);
	sit_t from = SrtLBegin(src);
	sit_t to = from;
	sit_t src_end = SrtLEnd(src);
	scmp_f isBefore = GetIsBefore(dest);
	int is_done = 0;
	
	assert(NULL != dest);
	assert(NULL != src);

	while (!is_done)
	{
		if(ISBF(from, where)) /* if where is lower/equal than from */
		{
			where = SrtLNext(where);
			if(dest_end == where)
			{
				to = src_end;
				DLLSpliceBefore(where, from, to);
				is_done = 1;
				continue;
			}
		}
		if(ISBF(where, to)) /* if where is higher/equal than to */
		{
			to = SrtLNext(to);
			if(src_end == to)
			{
				DLLSpliceBefore(where, from, to);
				is_done = 1;
				continue;
			}
		}			
		if(!is_done && !ISBF(where, to) && ISBF(where, from)) /* if where is in [from, to)*/
		{
			DLLSpliceBefore(where, from, to);
			from = to;	
			if (SrtLNext(where) == dest_end) 
			{
				to = src_end;
				where = dest_end;
				DLLSpliceBefore(where, from, to);
				is_done  = 1;
				continue;
			}
			
			where = SrtLNext(where);
		}	
	}	
}

/* service functions */
static scmp_f GetIsBefore (srtl_t *list)
{
	return list->is_before;
}
