/*******************************************
 **           Author: Mishel Liberman     **
 **			  		Reviewer: Daniel Maizel  	  **
 **           Date: 06.06.19              **
 *******************************************/
#include <stdlib.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /*strcmp */

#include "../../include/DLL/dll.h" /* My header file */

struct DLLnode               
{
	void *data;
	struct DLLnode *next;
	struct DLLnode *prev;
};

struct DLL
{
	struct DLLnode *head;
	struct DLLnode *tail;
};

static it_t CreateNode(void *data, it_t next, it_t prev)
{
	it_t node = (it_t)malloc(sizeof(struct DLLnode));
	if(NULL == node)
	{
		return NULL;
	}
	
	node->next = next;
	node->prev = prev;
	node->data = data;
	
	return node;
}

dll_t *DLLCreate()
{
	dll_t *dll = (dll_t*)malloc(sizeof(dll_t));
	if(NULL == dll)
	{
		return NULL;
	}
	
	dll->head = CreateNode((void *)0xDEADBEEF, NULL, NULL);
	dll->tail = CreateNode((void *)0xDEADBEEF, NULL, dll->head);
	dll->head->next = dll->tail;
	
	return dll;
}

void DLLDestroy(dll_t *dll)
{
	it_t node = dll->head;
	it_t next_node = NULL;
	assert(NULL != dll);
	
	while(NULL != node)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
	
	free(dll);
}

it_t DLLBegin(const dll_t *dll)
{
	assert(NULL != dll);
	
	return dll->head->next;
}

it_t DLLEnd(const dll_t *dll)
{
	assert(NULL != dll);
	
	return dll->tail;
}

it_t DLLNext(const it_t iter) 
{
	assert(NULL != iter);
	
	return iter->next;
}

it_t DLLPrev(const it_t iter) 
{
	assert(NULL != iter);
	
	return iter->prev;
}

it_t DLLPushBack(dll_t *dll, const void *data)
{
	it_t temp =NULL;
	it_t new_node = NULL;
	
	assert(NULL != data);
	
	new_node = CreateNode((void*)data, dll->tail, dll->tail->prev);
	temp = dll->tail->prev;
	dll->tail->prev = new_node;
	temp->next = new_node;
	
	return new_node;
}

it_t DLLPushFront(dll_t *dll, const void *data)
{
	it_t begin = DLLBegin(dll);
	it_t new_node = NULL;
	
	assert(NULL != dll && NULL != data);
	
	new_node = CreateNode((void*)data, begin, dll->head);
	dll->head->next = new_node;
	begin->prev = new_node;
	
	return new_node;
}

void *DLLGetData(const it_t iter)
{
	assert(NULL != iter);
	
	return iter->data;
}

int DLLIsSameIter(const it_t iter1,const it_t iter2)
{
	assert(NULL != iter1 && NULL != iter2);
	
	return (iter1 == iter2);
}

void DLLPopBack(dll_t *dll) 
{
	if(!DLLIsEmpty(dll))
	{
		it_t end = DLLEnd(dll);
		it_t before_end = end->prev;
		it_t before_before_end = before_end->prev;
			
		before_before_end->next = end;
		end->prev = before_before_end;
		free(before_end);
	}
}

void DLLPopFront(dll_t *dll)
{
	if(!DLLIsEmpty(dll))
	{
		it_t begin = DLLBegin(dll);
		it_t head = begin->prev;
		it_t after_begin = begin->next;
		
		after_begin->prev = head;
		head->next = after_begin;
		free(begin);
	}
}

size_t DLLSize(const dll_t *dll)
{
	int count = 0;
	it_t end = DLLEnd(dll);
	
	it_t current = DLLBegin(dll);
	
	while(current != end)
	{
		++count;
		current = current->next;
	}
	
	return count;
}

int DLLIsEmpty(const dll_t *dll) /* 1 For Empty */
{
	return (0 == DLLSize(dll));
}

it_t DLLInsert(dll_t *dll, it_t iter, const void *data)
{
	it_t current = DLLBegin(dll);
	it_t new_node = NULL;
	
	assert(NULL != data && NULL != iter);
	
	while(current != iter)
	{
		current = DLLNext(current);
	}
	
	new_node = CreateNode((void*)data , DLLNext(iter), iter);
	iter->next = new_node; 
	new_node->next->prev = new_node;
	
	return new_node;
}

int DLLForEach(it_t from, it_t to, act_f action, void* params)
{
	it_t current = from;
	
	assert(NULL != from && NULL != to);
	
	for(; current != to; current = DLLNext(current))
	{
		if(1 == action(current->data, params))
		{
			return 1;
		}
	}
	
	return 0;
}

it_t DLLFind(it_t from, it_t to, cmp_f compare, void* params, void* data)
{
	it_t	current = from;
	
	assert(NULL != from && NULL != to);
	
	for(; current != to; current = DLLNext(current))
	{
		if(1 == compare(current->data, data))
		{
			return current;
		}
	}
	
	return to;
}

it_t DLLErase(it_t where) 
{
	it_t where_next = where->next;
	where->prev->next = where->next;
	where->next->prev = where->prev;
	free(where);
	
	return where_next;
}


it_t DLLSpliceBefore(it_t where, it_t from, it_t to)
{
	it_t before_to = NULL;
	it_t before_from = NULL;
	it_t before_where = NULL;
	
	assert(NULL != where && NULL != from && NULL != to);
	
	before_to = to->prev;
	before_from = from->prev;
	before_where = where->prev;

	before_to->next = where;
	before_where->next = from;
	to->prev = before_from;
	from->prev->next = to;
	before_from = to;
	where->prev = before_to;
	
	return from;	
}


























