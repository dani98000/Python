/********************************
*	Author: Eran Segal			*
*	Reviewer: Daniel Maizel		*
*	Date: 6.6.19				*
********************************/


#include <stdio.h>	/* size_t */
#include <stdlib.h> /* malloc */

#include "../../include/SLL/sll.h"

#define STUB (void *)0xDEADBEEF
#define CREATE_CHECK(X) if(NULL == X) { return NULL; }
#define TAIL_FOR_FAIL(X, TAIL) NULL == X ? TAIL : X

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

static it_t SLLCreateNode(const void *data, it_t next_node)
{
	it_t node = (it_t)malloc(sizeof(struct node));
	CREATE_CHECK(node);
	node->data = (void *)data;
	node->next = next_node;
	
	return node;
}

static it_t SLLGetPointing(const sll_t *sll, it_t Pointed)
{
	it_t Runner = sll->head;
	
	while(Runner->next != Pointed)
	{
		Runner = Runner->next;
	}
	
	return Runner;
}

sll_t *SLLCreate()
{
	sll_t *sll = (sll_t *)malloc(sizeof(struct sll));
	CREATE_CHECK(sll);
	sll->tail = SLLCreateNode(STUB, NULL);
	sll->head = SLLCreateNode(STUB, sll->tail);

	return sll;
}

void SLLDestroy(sll_t *sll)
{
	it_t NRunner = sll->head;
	it_t NLiberator = NULL;
	
	while(NRunner->data != STUB)
	{
		NLiberator = NRunner;
		NRunner = NRunner->next;
		free(NLiberator);
	}
	
	free(NRunner);
	free(sll);
}

it_t SLLInsertAfter(sll_t *sll, it_t iter, const void *data)
{
	it_t new = SLLCreateNode(data, iter->next);
	iter->next = new;
	
	return TAIL_FOR_FAIL(new, sll->tail);
}

it_t SLLPushBack(sll_t *sll, const void *data)
{
	it_t back = SLLGetPointing(sll, sll->tail);
	it_t new_node = (it_t)malloc(sizeof(struct node));
	CREATE_CHECK(new_node);
	new_node->data = (void *)data;
	new_node->next = sll->tail;
	
	back->next = new_node;
	
	return TAIL_FOR_FAIL(new_node, sll->tail);
}

it_t SLLPushFront(sll_t *sll, const void *data)
{
	sll->head->next = SLLCreateNode(data, sll->head->next);
	
	return TAIL_FOR_FAIL(sll->head->next, sll->tail);
}

void SLLErase(sll_t *sll, it_t where)
{
	it_t pointing_to_erased = SLLGetPointing(sll, where);
	pointing_to_erased->next = where->next;
	free(where);
}

void SLLPopBack(sll_t *sll)
{
	it_t back = SLLGetPointing(sll, sll->tail);
	SLLErase(sll, back);
}

void SLLPopFront(sll_t *sll)
{
	SLLErase(sll, sll->head->next);
}

void *SLLGetData(const it_t iter)
{
	return iter->data;
}

it_t SLLBegin(const sll_t *sll)
{
	return sll->head->next;
}

it_t SLLEnd(const sll_t *sll)
{
	return sll->tail;
}

it_t SLLNext(const it_t iter)
{
	return iter->next;
}

int SLLIsEmpty(const sll_t *sll)
{
	return sll->head->next == sll->tail;
}

size_t SLLSize(const sll_t *sll)
{
	size_t cnt = 0;
	it_t iter = sll->head;
	
	while(iter->next != sll->tail)
	{
		iter = iter->next;
		++cnt;
	}
	
	return cnt;
}

it_t SLLFind(it_t from, it_t to, void *key, cmp_f compare)
{
	it_t iter = from;
	
	while(iter != to && 0 == compare(iter->data, key))
	{
		iter = iter->next;
	}
	
	return iter;
}

int SLLForEach(it_t from, it_t to, const void *param, act_f action)
{
	it_t iter = from;
	int error;
	
	while(iter != to && 0 == error)
	{
		error = action(iter->data, param);
		iter = iter->next;
	}
	
	return error;
}

sll_t *SLLFLip(sll_t *sll)
{
	it_t fliper = sll->tail;
	do
	{
		fliper->next = SLLGetPointing(sll, fliper);
		fliper = fliper->next;
	}
	while(fliper != sll->head);
	
	sll->head = sll->tail;
	sll->tail = fliper;
	sll->tail->next = NULL;
	
	return sll;
}


/*
int SLLHasLoop(const sll_t *sll)
{
	
}

it_t SLLFindIntersection(const sll_t *sll1, const sll_t *sll2)
{
	
}
*/

