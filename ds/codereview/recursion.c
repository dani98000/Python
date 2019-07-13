/***************************************
* DATA STRUCTURES: Recursion         *
* CODE BY:         SANDRA HADAD        *   
* REVIEWED BY:     SANDRA HADAD        *                          
****************************************/ 
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <stdio.h> /* printf */

#include "../include/recursion.h"
#include "../include/stack.h"

long IterFibonacci(long n)
{
	long f0 = 0, f1 = 1, f2 = 1;
	int i = 1;
	
	if(0 == n)
	{
		return 0;
	}
	
	if(1 == n)
	{
		return 1;
	}
	
	for(;i < n; ++i)
	{
		f2 = f0 + f1;
		f0 = f1;
		f1 = f2;
	}
	
	return f2;
}

long RecurFibonacci(long n)
{
	
	if(0 == n)
	{
		return 0;
	}
	
	if(1 == n)
	{
		return 1;
	}		
	return RecurFibonacci(n - 1) + RecurFibonacci(n - 2);
}

size_t RecurStrlen(const char *s)
{
	char *runner = (char *)s;
	
	if('\0' == *runner)
	{
		return 0;
	}
	
	++runner;
	
	return 1 + RecurStrlen(runner);
}

int RecurStrcmp(const char *s1, const char *s2)
{
	char *runner1 = (char *)s1;
	char *runner2 = (char *)s2;
	
	if('\0' == *runner1 && '\0' == *runner2)
	{
		return 0;
	}
	
	if(*runner1 != *runner2)
	{
		return *runner1 - *runner2;
	}
	
	return RecurStrcmp(++runner1, ++runner2);
}

char *RecurStrcpy(char *dest, const char *src)
{
	char *runner_src = (char *)src;
	char *runner_dest = dest;
	
	*runner_dest = *runner_src;
	
	if(*runner_src == '\0')
	{
		return dest;
	}
	
	return RecurStrcpy(++runner_dest, ++runner_src);
}

node_t *RecurFlip(node_t *head)
{
	node_t *return_node = NULL;
	
	if(NULL == head->next)
	{
		return head;
	}
	
	return_node = RecurFlip(head->next);
	head->next->next = head;
	head->next = NULL;
	
	return return_node;
}


static void Insert(stack_t *stack, int num)
{
		int temp = 0;
		
		if(0 == STACKSize(stack) || num < *(int *)STACKPeek(stack))
		{
			STACKPush(stack, &num);
			
			return;		
		}	
			
		temp = *(int *)STACKPeek(stack);
		STACKPop(stack);
		Insert(stack, num);
		STACKPush(stack,&temp);
	
}

void RecurStackSort(stack_t *stack)
{
	int num = 0;
		
	if(0 != STACKSize(stack))
	{
		num = *(int *)STACKPeek(stack);
		STACKPop(stack);
		RecurStackSort(stack);
		Insert(stack,num);
	}
}

/*void RecurStackSort(stack_t *stack)
{
	int num = 0;
	
	num = *(int *)STACKPeek(stack);
	STACKPop(stack);
	
	if(0 == STACKSize(stack) || num > *(int *)STACKPeek(stack))
	{
		printf("here\n");
		STACKPush(stack, &num);
		return;	
	}

	RecurStackSort(stack);
	printf("here1\n");
	
	STACKPush(stack, &num);
	
	return;
}*/

/*
char *RecurStrcat(char *dest, const char *src);
{
	return 1;
}

char *RecurStrstr(const char *haystack, const char *needle);
{
	return 1;
}

*/
