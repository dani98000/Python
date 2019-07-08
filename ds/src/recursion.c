#include <stdio.h>
#include "../include/recursion.h"



int FibRec(int n)
{
	if(n == 0 || n == 1)
	{
		return 1;
	}
	
	return(FibRec(n-1) + FibRec(n-2));
}

int FibIter(int n)
{
	int current = 1;
	int prev = 1;
	int next = 2;
	size_t counter = 0;
	
	while(counter < n - 1)
	{
		prev = current;
		current = next;
		next = prev + current;
		++counter;
	}
	
	return current;
}

int str_len(char *str)
{
	char *runner = str;
	if('\0' == *runner)
	{
		return 0;
	}
	
	++runner;
	
	return str_len(runner) + 1;
}

int str_cmp(char *str1, char *str2)
{
	char *runner1 = str1;
	char *runner2 = str2;
	
	if(*runner1 != *runner2 || *(runner1+1) == '\0')
	{
		return *runner1 - *runner2;
	}
	
	++runner1;
	++runner2;
	
	return(str_cmp(runner1, runner2));
}

char *str_cpy(char *dest, const char *src)
{
	char *dest_runner = dest;
	char *src_runner = (char *)src;
	
	if(*src_runner == '\0')
	{
		*dest_runner = '\0';
		return dest;
	}
	
	*dest_runner = *src_runner;
	++dest_runner;
	++src_runner;
	
	return str_cpy(dest_runner, src_runner);
}

node_t *RecurFlip(node_t *head)
{
	node_t *rest = NULL;
	
	if(head->next == NULL)
	{
		return head;
	}
	
	rest = RecurFlip(head->next);
	head->next->next = head;
	head->next  = NULL;
	
	return rest;
}

void RecurStackSort(stack_t *stack)
{
	int temp = 0;	
	
	if(STACKSize(stack) > 0)
	{
		temp = *(int *)STACKPeek(stack);
		STACKPop(stack);
		if(*(int *)STACKPeek(stack) < temp)
		{
			STACKPush(stack, &temp);
			
		}
		else
		{

			if(*(int *)STACKPeek(stack) > temp)
			{				
				/*STACKPush(stack, &temp);*/
			RecurStackSort(stack);
				/*STACKPop(stack);*/
			}
			else
			{

				STACKPush(stack, &temp);
			}
			
		}

	}
	
}
