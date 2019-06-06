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
	char c = '4';
	char d = '5';
	char a = '6';
	char x = '1';
	char y = '2';
	char z = '3';
	char n = 0;

	queue_t *queue = QueueCreate();
	queue_t *dest = QueueCreate();
	queue_t *res = NULL;
	
	QueueEnqueue(queue, (void*)&c);
		QueueEnqueue(queue, (void*)&d);
			QueueEnqueue(queue, (void*)&a);
	n = *((char *)QueuePeek(queue));
	printf("%c\n",n);
	

	QueueEnqueue(dest, (void*)&x);
	QueueEnqueue(dest, (void*)&y);
			printf(" Dest size = %d\n",QueueSize(dest));
	QueueEnqueue(dest, (void*)&z);
	
		printf(" Dest size = %d\n",QueueSize(dest));
	SLLForEach(SLLBegin(*(sll_t **)dest), SLLEnd(*(sll_t**)dest), *(sll_t**)dest, print_list);
	
		res = QueueAppend(queue,dest);
			SLLForEach(SLLBegin(*(sll_t **)res), SLLEnd(*(sll_t**)res), *(sll_t**)res, print_list);
		QueueDestroy(queue);
		QueueDestroy(dest);
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
