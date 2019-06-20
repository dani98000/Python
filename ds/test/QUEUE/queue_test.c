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
int Test_QueueEnqueue(void);
int Test_QueueDequeue(void);
int Test_QueueAppend(void);



/*void test()
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
}*/

int print_list(void *data, const void *arg)
{
    printf("%d->", *(int *)data);   
    return 0;
}

int main()
{
	/*test();*/
	RUN_TEST(Test_QueueEnqueue);
	RUN_TEST(Test_QueueDequeue);	
	RUN_TEST(Test_QueueAppend);
	
	
	
	return 0;
}

int Test_QueueEnqueue(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	queue_t *queue = QueueCreate();
	
	int x = 1;
	int y = 2;
	int z = 3;
	int n = 0;
	
	/* test1 */
	res = QueueSize(queue);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	QueueEnqueue(queue, (void*)&x);
	QueueEnqueue(queue, (void*)&y);
	
	/* test2 */
	res = QueueSize(queue);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((int *)QueuePeek(queue));
	
	/* test 3 */
	res = n;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	QueueEnqueue(queue, (void*)&z);
	
	/* test4 */
	res = QueueSize(queue);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test 5 */
	res = n;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	QueueDestroy(queue);

	return result;
}

int Test_QueueDequeue(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	queue_t *queue = QueueCreate();
	
	int x = 1;
	int y = 2;
	int z = 3;
	int n = 0;
	
	/* test1 */
	res = QueueSize(queue);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	QueueEnqueue(queue, (void*)&x);
	QueueEnqueue(queue, (void*)&y);
	QueueEnqueue(queue, (void*)&z);
	
	
	/* test2 */
	res = QueueSize(queue);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((int *)QueuePeek(queue));
	
	/* test 3 */
	res = n;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	QueueDequeue(queue);
	
	/* test4 */
	res = QueueSize(queue);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((int *)QueuePeek(queue));
	
	/* test 5 */
	res = n;
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	QueueDequeue(queue);
	n = QueueIsEmpty(queue);
	
	/* test 6 */
	res = n;
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	QueueDequeue(queue);
	
	n = QueueIsEmpty(queue);
	
	/* test 7 */
	res = n;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	QueueDestroy(queue);

	return result;
}

int Test_QueueAppend()
{
	int c = 4;
	int d = 5;
	int a = 6;
	int x = 1;
	int y = 2;
	int z = 3;
	int n = 0;

	queue_t *src = QueueCreate();
	queue_t *dest = QueueCreate();
	queue_t *res = NULL;
	
	QueueEnqueue(src, (void*)&c);
		QueueEnqueue(src, (void*)&d);
			QueueEnqueue(src, (void*)&a);

	QueueEnqueue(dest, (void*)&x);
	QueueEnqueue(dest, (void*)&y);
	QueueEnqueue(dest, (void*)&z);
	
	/*SLLForEach(SLLBegin(*(sll_t **)dest), SLLEnd(*(sll_t**)dest), *(sll_t**)dest, print_list);*/
	res = QueueAppend(dest,src);
	printf("\tafter append:\n");
	printf("\t");
	SLLForEach(SLLBegin(*(sll_t **)res), SLLEnd(*(sll_t**)res), *(sll_t**)res, print_list);
	    printf("NULL\n");
	
	
	QueueDestroy(src);
	QueueDestroy(dest);
}
