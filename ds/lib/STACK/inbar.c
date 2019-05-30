/*************************************************************************************/
/* Author- Inbar Namdar                                                              */
/* Reviewer - Daniel                                                                 */
/* Date - 28/5/2019                                                                  */
/*************************************************************************************/

#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "../../include/STACK/stack.h"

static int IsEmpty(const stack_t *stack);
static int IsFull(stack_t *stack);

struct Stack 
{
	void *current;
	void *end;
	size_t element_size;
	char head[1];
};

void STACKPop(stack_t *stack)
{
	if (!IsEmpty((const stack_t *)stack))
	{
		stack->current = (char *)stack->current - stack->element_size;
	}
}

int STACKPush(stack_t *stack, const void *element)
{
	assert(NULL != element);
	if (IsFull(stack))
	{
		return 1;
	}
	
	memcpy(stack->current, element, stack->element_size);  
	stack->current = (char *)stack->current + stack->element_size;
	
	return 0;
}

void *STACKPeek(const stack_t *stack)
{
	if (IsEmpty(stack))
	{
		return NULL;
	}
	return (char *)stack->current - stack->element_size;
}

stack_t *STACKCreate(size_t n_elements, size_t size_of_element)
{
	stack_t *stack = NULL;
	assert(n_elements > 0);
	assert(size_of_element > 0);
	
	stack = (stack_t *)malloc(sizeof(stack_t) - 7 + (size_of_element * n_elements) );
	if (NULL == stack)
	{
		return NULL;
	}
	
	stack->current = stack->head;
	stack->end = stack ->head + (size_of_element * n_elements);
	stack->element_size = size_of_element; 
	
	return stack; 
}

size_t STACKSize(const stack_t *stack)
{
	return (int *)(stack -> current) - (int *)(stack -> head);
}

void STACKDestroy(stack_t *stack)
{
	free(stack);
}

static int IsEmpty(const stack_t *stack)
{
	return ((char *)stack->current > (char *)stack->head) ? 0 : 1;
}

static int IsFull(stack_t *stack)
{
	return ((char *)stack->end > (char *)stack->current) ? 0 : 1;		
}
