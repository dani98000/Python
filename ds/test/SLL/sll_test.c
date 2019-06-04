#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../../include/SLL/sll.h"

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

/*void test()
{
	char c = '5';
	char d = 'a';
	size_t size = 0;
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;
	sll_t *sll = SLLCreate();
	printf("before push:%lu\n",SLLSize(sll));
	iter1 = SLLPushFront(sll, (void*)&c);
	printf("after push%lu\n",SLLSize(sll));
	n = *((char *)SLLGetData((void *)iter1));
	printf("%c\n",n);
	
	iter2 = SLLPushBack(sll, (void *)&d);
	printf("after push%lu\n",SLLSize(sll));
	n = *((char *)SLLGetData((void *)iter2));
	printf("%c\n",n);
	iter2=SLLBegin(sll);
	n = *((char *)SLLGetData((void *)iter2));
	printf("%c\n",n);
	SLLPushFront(sll, (void*)&d);
	SLLPushBack(sll, (void*)&d);
	n = *((char *)SLLGetData((void *)SLLBegin(sll)));
	printf("%c\n",n);
	
	
	
	
	
	
	SLLDestroy(sll);
}*/


int Test_SLLPushBack(void);
int Test_SLLPushFront(void);
int Test_SLLInsertAfter(void);
int Test_SLLIsEmpty(void);
int Test_SLLPopFront

int main()
{
	/*test();*/
	RUN_TEST(Test_SLLPushBack);
	RUN_TEST(Test_SLLPushFront);
	RUN_TEST(Test_SLLInsertAfter);
	
	
	
	
	return 0;
}

int Test_SLLPushBack(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 5;
	int d = 8;
	char n = 0;
	it_t iter1 = NULL;
	sll_t *sll = SLLCreate();
	
	/* test1 */
	res = SLLSize(sll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = SLLPushFront(sll, (void*)&c);
	n = *((char *)SLLGetData((void *)iter1));

	/* test2 */
	res = n;
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	
	/* test3 */
	res = SLLSize(sll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = SLLPushFront(sll, (void*)&d);
	n = *((char *)SLLGetData((void *)iter1));

	/* test4 */
	res = n;
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((char *)SLLGetData(SLLBegin(sll)));
	
	/* test7 */
	res = n;
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test8 */
	res = SLLSize(sll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	SLLDestroy(sll);

	return result;
}

int Test_SLLPushFront(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 5;
	int d = 8;
	char n = 0;
	it_t iter1 = NULL;
	sll_t *sll = SLLCreate();
	
	/* test1 */
	res = SLLSize(sll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = SLLPushBack(sll, (void*)&c);
	n = *((char *)SLLGetData((void *)iter1));

	/* test2 */
	res = n;
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	
	/* test3 */
	res = SLLSize(sll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = SLLPushBack(sll, (void*)&d);
	n = *((char *)SLLGetData((void *)iter1));

	/* test4 */
	res = n;
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((char *)SLLGetData(SLLBegin(sll)));
	
	/* test7 */
	res = n;
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test8 */
	res = SLLSize(sll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	SLLDestroy(sll);
	
	return result;
}

int Test_SLLInsertAfter(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 5;
	int d = 8;
	int e = 9;
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;
	it_t iter3 = NULL;
	sll_t *sll = SLLCreate();
	
	/* test1 */
	res = SLLSize(sll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = SLLPushBack(sll, (void*)&c);
	n = *((char *)SLLGetData((void *)iter1));

	/* test2 */
	res = n;
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	iter2 = SLLPushBack(sll, (void*)&d);
	n = *((char *)SLLGetData((void *)iter2));

	/* test3 */
	res = n;
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test4 */
	res = SLLSize(sll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	iter3 = SLLInsertAfter(sll, iter1, &e);
	n = *((char *)SLLGetData((void *)iter3));
	
	/* test5 */
	res = n;
	expect = 9;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test6 */
	res = SLLSize(sll);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((char *)SLLGetData(SLLNext(iter1)));
	
	/* test7 */
	res = n;
	expect = 9;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	SLLDestroy(sll);
	
	return result;
}


