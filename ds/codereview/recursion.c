#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/recursion.h"


long IterFibonacci(long n)
{
    long prev = 1;
    long current = 1;
    long temp = 0;
    long i = 2;
   
    if (1 == n || 2 == n)
    {
        return 1;
    }
    
    for (; i <= n; ++i)
    {
        temp = current;
        current = current + prev;
        prev = temp;
    }
    
    return prev;
}

long RecurFibonacci(long n)
{
    if (n <= 1)
    {
        return n;
    }
    
    return RecurFibonacci(n-1) + RecurFibonacci(n-2);
}

size_t RecurStrlen(const char *s)
{
    static size_t counter = 0;
    
    if ('\0' == *s)
    {
        return counter;
    }
    
    ++counter;
    ++s;
    
    return RecurStrlen(s);
}

int RecurStrcmp(const char *s1, const char *s2)
{	
	if ('\0' == *s1 || '\0' == *s2)
	{
		return 0;
	}
		
	if (*s1 != *s2)
	{
		return *s1 - *s2;
	}
	
	++s1;
	++s2;
		
	return RecurStrcmp(s1, s2);
}

char *RecurStrcpy(char *dest, const char *src)
{
    if ('\0' == *src)
    {
        return dest;
    }

    *dest = *src;
    ++dest;
    ++src;
    
    return RecurStrcpy(dest, src);
}

node_t *RecurFlip(node_t *head)
{
	node_t *rest_of_list = head->next;
	node_t *temp = NULL;
	
  if (NULL == rest_of_list)
  {
  	return NULL;
  }
  
  temp = RecurFlip(rest_of_list);
  rest_of_list->next = head;
  head->next = NULL;
  
  return temp;
}

void RecurStackSort(stack_t *stack)
{
    int *temp1 = 0;
    int *temp2 = 0;
    int bigger = 0;
    int smaller = 0;
    
    temp1 = STACKPeek(stack);
    STACKPop(stack);
        
    if (1 < STACKSize(stack))
    {
        RecurStackSort(stack);
    }
    
    temp2 = STACKPeek(stack);
    STACKPop(stack);
    
    bigger = (*temp1 >= *temp2) ? *temp1 : *temp2;
    smaller = (*temp1 < *temp2) ? *temp1 : *temp2;
    
    STACKPush(stack, &bigger);
    
    if (1 < STACKSize(stack))
    {
        RecurStackSort(stack);
    }
    
    STACKPush(stack, &smaller);
}
