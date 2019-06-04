#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include "../../include/SLL/sll.h"


struct node
{
    void *data;
    struct node *next;
};

struct sll
{
    struct node *head;
    struct node *tail;
};

static it_t SLLCreateNode(const void *data,it_t next)
{
	it_t node = (it_t)malloc(sizeof(struct node));
	if(NULL == node)
	{
		free(node);
		return NULL;
	}
	
	node->data = (void *)data;
	node->next = next;
	return node;
}

sll_t *SLLCreate()
{
	sll_t *sll = (sll_t *)malloc(sizeof(sll_t));
	if(NULL == sll)
	{
		free(sll);
		return NULL;
	}
	
	sll->tail = SLLCreateNode((void *)0xDEADBEEF,NULL);
	sll->head = SLLCreateNode((void *)0xDEADBEEF,sll->tail);
	
	return(sll);
}

void SLLDestroy(sll_t *sll)
{
	it_t current = sll->head;  
	it_t temp = NULL;
	assert(NULL != sll);
	
	while(NULL != current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	free(sll);
}

it_t SLLInsertAfter(sll_t *sll, it_t iter, const void *data)
{
	it_t current = sll->head;
	it_t new_node = NULL;
	assert(NULL != sll);
	
	while (current->next != iter)
	{
		current = current->next;
  	}
	new_node = SLLCreateNode(data,iter->next);
	iter->next = new_node;
	
	return(new_node);
	
}
void SLLPopBack(sll_t *sll)
{
	it_t current = sll->head;  
	assert(NULL != sll);
	
	/*if(SLLSize(sll) == 0)
	{

	}*/
	while(current->next != sll->tail)
	{
		current = current->next;
	}
	
	SLLErase(sll,current);
}

void SLLPopFront(sll_t *sll)
{
	assert(NULL != sll);
	
	SLLErase(sll,sll->head->next);
}

it_t SLLPushBack(sll_t *sll, const void *data)
{
	it_t runner = sll->head;
	it_t new_node = NULL;
	assert(NULL != sll);
	
     
    while(runner->next != sll->tail)
    {
         runner = runner->next;
    }
    
	new_node = SLLCreateNode(data ,sll->tail);
	runner->next = new_node;
	
	
	return (new_node);
}

it_t SLLPushFront(sll_t *sll, const void *data)
{
	it_t new_node = SLLCreateNode(data ,sll->head->next);
	assert(NULL != sll);
	
	sll->head->next = new_node;
	
	return (new_node);
}

void *SLLGetData(it_t iter)
{
	return(iter->data); 
}
it_t SLLBegin(const sll_t *sll)
{
	assert(NULL != sll);
	
	return(sll->head->next);
}

it_t SLLEnd(const sll_t *sll)
{
	assert(NULL != sll);
	
	return(sll->tail);
}

it_t SLLNext(it_t iter)
{
	return(iter->next);
}

/*int SLLForEach(it_t from, it_t to, const void *param, act_f action);
it_t SLLFind(it_t from, it_t to, void *key, cmp_f compare);*/

int SLLIsEmpty(const sll_t *sll)
{
	assert(NULL != sll);
	
	return(sll->head->next == sll->tail);
}

size_t SLLSize(const sll_t *sll)
{
	it_t current = sll->head;
	size_t count = 0;
	assert(NULL != sll);
	
	while(current->next != sll->tail)
	{
		current = current->next;
		++count;
	}
	
	return count;
}

/*sll_t *SLLFLip(sll_t *sll);*/
void SLLErase(sll_t *sll, it_t where) /* erases given iterator from list*/
{
	it_t p_to_where = sll->head;
	assert(NULL != sll);
	
     
	while(p_to_where->next != where)
    {
         p_to_where = p_to_where->next;
    }
     
    p_to_where->next = where->next;
    free(where);
} 

/*int SLLHasLoop(const sll_t *sll);
it_t SLLFindIntersection(const sll_t *sll1, const sll_t *sll2);*/


