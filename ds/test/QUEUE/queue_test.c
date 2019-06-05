#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "../../include/SLL/sll.h"
#include "../../include/QUEUE/queue.h"

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
int print_list(void *data, const void *arg);
void test()
{
	char c = '5';
	char d = 'a';
	char a = 'z';
	char x = '1';
	char y = '2';
	char z = '3';
	char n = 0;
	it_t iter1 = NULL;

	queue_t *queue = QueueCreate();
		queue_t *dest = QueueCreate();
	
	QueueEnqueue(queue, (void*)&c);
	n = *((char *)QueuePeek(queue));
	printf("%c\n",n);
	
	printf("size = %d\n",QueueSize(queue));
	QueueDequeue(queue);
		printf("size = %d\n",QueueSize(queue));
		
		printf("is empty: %d",QueueIsEmpty(queue));
	QueueDequeue(queue);
			printf("is empty: %d",QueueIsEmpty(queue));
		printf("size = %d\n",QueueSize(queue));
	

	QueueEnqueue(dest, (void*)&x);
	QueueEnqueue(dest, (void*)&y);
	QueueEnqueue(dest, (void*)&z);
	
	SLLForEach(SLLBegin(*(sll_t **)dest), SLLEnd(*(sll_t**)dest), *(sll_t**)dest, print_list);
	
	QueueDestroy(queue);
}

int print_list(void *data, const void *arg)
{

    printf("%c->", *(char *)data);   
    return 0;
}

int main()
{
	test();
	return 0;
}
