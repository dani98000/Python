/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Sandra         	*
*								*
*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "sll.h" /* My Header */

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
	it_t new_node = NULL;
	assert(NULL != sll);
	
	new_node = SLLCreateNode(data,iter->next);
	iter->next = new_node;
	
	return(new_node);
	
}
void SLLPopBack(sll_t *sll)
{
	it_t current = sll->head;  
	assert(NULL != sll);
	
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

int SLLForEach(it_t from, it_t to, const void *param, act_f action)
{
	it_t current = NULL;
	int res = 0;
	
	for(current = from; current != to ; current = current->next)
	{
		res = (action)(current->data, param);
		if(res != 0)
		{
			return res;
		} 
	}
	
	return 0;
}

it_t SLLFind(it_t from, it_t to, void *key, cmp_f compare)
{
	it_t current = NULL;
	int res = 1;

	for(current = from; current != to ; current = current->next)
	{
		res = (compare)(current->data, key);
		if(res != 0)
		{
			return current;
		}
	}
	
	return to;
}

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

sll_t *SLLFLip(sll_t *sll)
{
	it_t prev   = NULL; 
    it_t current = sll->head; 
    it_t next = NULL;
    sll->tail = sll->head; 
    
    while (current != NULL) 
    { 
        next  = current->next;   
        current->next = prev;    
        prev = current; 
        current = next; 
    } 
    sll->head = prev; 
	
	return(sll);
}

void SLLErase(sll_t *sll, it_t where) 
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

/*it_t SLLFindIntersection(const sll_t *sll1, const sll_t *sll2)
{
	it_t runner1 = sll1->head;
	it_t runner2 = sll2->head;
	size_t size1 = SLLSize(sll1);
	size_t size2 = SLLSize(sll2);
	size_t length = 0;
	
	while(SLLSize(sll1) != SLLSize(sll2))
	{
		if(size1 > size2)
		{
		
		}
	
	while(runner1->next != runner2->next)
	{
		runner1 = runner1->next;
		runner2 = runner2->next;
	}
	
	return(runner1->next);
}*/
