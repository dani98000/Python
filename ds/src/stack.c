/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Eldad Carin    	*
*								*
*********************************/

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* size_t */
#include <assert.h> /* assert */

#include "../include/stack.h"

struct Stack
{
	void *current;
	void *end;
	size_t size_of_element;
	char head[1];
};

void STACKPop(stack_t *stack)
{
	assert(NULL != stack);
		
	if((STACKSize(stack)) > 0)
	{
		stack->current = (char *)stack->current - stack->size_of_element;
	}
}

int STACKPush(stack_t *stack, const void *element)
{
	assert(NULL != stack);
	
	if((char *)stack->current >= ((char *)stack->end - 1))
	{
		return 1;
	}
	
	memcpy(stack->current, element, stack->size_of_element);
	stack->current = ((char *)stack->current + stack->size_of_element);
	
	return 0;
}

void *STACKPeek(const stack_t *stack)
{
	if((STACKSize(stack))<1)
	{
		return NULL;
	}
	else
	{
		return((char *)stack->current - stack->size_of_element);
	}
}

stack_t *STACKCreate(size_t n_elements, size_t size_of_element)
{
	stack_t *stack1 = NULL;
	assert(n_elements > 0);
	
	stack1 = (stack_t *)malloc(sizeof(stack_t) + (n_elements * size_of_element)-7);

	if (NULL == stack1)
	{
		return NULL;
	}
	
	stack1->size_of_element = size_of_element;
	stack1->current = (stack1->head);
	stack1->end = (char *)stack1 + (sizeof(stack_t) + (n_elements * size_of_element)-7);
	
	return stack1;
}

size_t STACKSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (((size_t)stack->current - (size_t)&stack->head) / stack->size_of_element);
}

void STACKDestroy(stack_t *stack)
{
	free(stack);
}
