#include <stdio.h>

#include "stack.h"

#define RUN_TEST(test)\
if(!test())\
{\
printf("\033[1;31m");\
printf(#test " - failed!\n");\
printf("\033[0m");\
}\
else\
{\
printf("\033[1;32m");\
printf(#test " - ok!\n");\
printf("\033[0m");\
}

int test_pushpeek();
int test_pop();
int test_size();

int main()
{
	RUN_TEST(test_pushpeek);	
	RUN_TEST(test_pop);		
	RUN_TEST(test_size);		
	
	return 0;
}


int test_pushpeek()
{
	stack_t *stack = STACKCreate(1, sizeof(int)); 
	int n = 0;
	int x = 4;
	int y = 5;
	int s = 6;
	int result = 1;
	STACKPush(stack, &y); 
	n = *((int *)STACKPeek((void *)stack)); 
	printf("%d",n);
	result *= (n == 5);
	STACKPush(stack, &x); 
	n = *((int *)STACKPeek((void *)stack)); 
	printf("%d",n);
	result *= (n == 5);
	STACKPop((void *)stack);
	STACKPush(stack, &s); 
	n = *((int *)STACKPeek((void *)stack)); 
	result *= (n == 6);

	STACKDestroy(stack);
	return result;
}

int test_pop()
{
	stack_t *stack = STACKCreate(4, sizeof(int)); 
	int n = 0;
	int x = 4;
	int y = 5;
	int s = 6;
	int b = 8;
	int result = 1;
	
	STACKPush(stack, &y); 
	STACKPush(stack, &x); 
	STACKPush(stack, &s); 
	STACKPush(stack, &b); 
	
	n = *((int *)STACKPeek((void *)stack));
	result *= (n == 8);
	STACKPop((void *)stack);
	n = *((int *)STACKPeek((void *)stack));
	result *= (n == 6);
	STACKPop((void *)stack);
	n = *((int *)STACKPeek((void *)stack));
	result *= (n == 4);
	STACKPop((void *)stack);
	n = *((int *)STACKPeek((void *)stack));
	result *= (n == 5);
	
	STACKDestroy(stack);
	return result;
}

int test_size()
{
	stack_t *stack = STACKCreate(4, sizeof(int)); 
	int x = 4;
	int y = 5;
	int s = 6;
	int b = 8;
	int result = 1;
	
	STACKPush(stack, &y); 
	STACKPush(stack, &x); 
	STACKPush(stack, &s); 
	STACKPush(stack, &b); 
	
	result *= (STACKSize(stack) == 4);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 3);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 2);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 1);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 0);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 0);
	
	STACKDestroy(stack);
	return result;
}
