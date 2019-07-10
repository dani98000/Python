#include <stdio.h>
#include "../include/recursion.h"

static void SortedInsert(stack_t *stack, int x);

long RecurFibonacci(long n)
{
	if(n == 0 || n == 1)
	{
		return n;
	}
	
	return(RecurFibonacci(n-1) + RecurFibonacci(n-2));
}

long IterFibonacci(long n)
{
	long current = 1;
	int prev = 0;
	int next = 1;
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

size_t RecurStrlen(const char *s)
{
	if('\0' == *s)
	{
		return 0;
	}
	
	return RecurStrlen(++s) + 1;
}

int RecurStrcmp(const char *s1, const char *s2)
{
	if(*s1 != *s2 || *(s1+1) == '\0')
	{
		return *s1 - *s2;
	}

	return(RecurStrcmp(++s1, ++s2));
}

char *RecurStrcpy(char *dest, const char *src)
{
	*dest = *src; 
	
	if(*src != '\0')
	{
		RecurStrcpy(++dest, ++src);
	}
	
	return dest;
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
		RecurStackSort(stack);
		SortedInsert(stack, temp);
	}
}

static void SortedInsert(stack_t *stack, int x)
{
	int temp = 0;	
	if(STACKSize(stack) > 0)
	{
		temp = *(int *)STACKPeek(stack);
		STACKPop(stack);
		
		if(x > temp)
		{
			SortedInsert(stack, x);
			STACKPush(stack, &temp);
		}
		else
		{
			STACKPush(stack, &temp);
			STACKPush(stack, &x);						
		}
	}
	else
	{
		STACKPush(stack, &x);						
	}
}

char *RecurStrcat(char *dest, const char *src)
{
	int size = RecurStrlen(dest);
	*(dest+size) = *src;

	if(*src == '\0')
	{
		return dest;
	}
	
	return RecurStrcat(++dest,++src);
}

char *RecurStrstr(const char *heystack, const char *needle)
{
	int niddle_size = RecurStrlen(needle);
	
	if(*(needle) == '\0')
	{
		return (char *)heystack - strlen(needle);
	}	
	else if(*(heystack + 1) == *(needle + 1))
	{
		return 	RecurStrstr(++heystack, ++needle);
	}
	
	return RecurStrstr(++heystack, needle);
}
