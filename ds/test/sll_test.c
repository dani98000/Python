#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "sll.h"

#define UNUSED(X) (void) (X)

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

int charcmp(const void *a, const void *b);
int print_list(void *data, const void *arg);
int Test_SLLPushBack(void);
int Test_SLLPushFront(void);
int Test_SLLInsertAfter(void);
int Test_SLLPopFront(void);
int Test_SLLPopBack(void);
int Test_SLLForEach(void);
int Test_SLLFind(void);
int Test_SLLFlip(void);
/*int Test_SLLFindIntersection();*/

int main()
{
	/*test();*/
	RUN_TEST(Test_SLLPushBack);
	RUN_TEST(Test_SLLPushFront);
	RUN_TEST(Test_SLLInsertAfter);
	RUN_TEST(Test_SLLPopFront);
	RUN_TEST(Test_SLLPopBack);
	RUN_TEST(Test_SLLFind);
	RUN_TEST(Test_SLLForEach);
	RUN_TEST(Test_SLLFlip);
	/*RUN_TEST(Test_SLLFindIntersection);*/
	
	
	
	
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

int Test_SLLPopFront(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 5;
	int d = 8;
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;
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
	
	SLLPopFront(sll);
	
	/* test5 */
	res = SLLSize(sll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((char *)SLLGetData(SLLBegin(sll)));
	
	/* test6 */
	res = n;
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	
	
	/* test7 */
	res = SLLIsEmpty(sll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	SLLPopFront(sll);
	
	/* test7 */
	res = SLLIsEmpty(sll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	SLLDestroy(sll);
	
	return result;
}

int Test_SLLPopBack(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 5;
	int d = 8;
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;

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
	
	SLLPopBack(sll);
	
	/* test5 */
	res = SLLSize(sll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((char *)SLLGetData(SLLBegin(sll)));
	
	/* test6 */
	res = n;
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	
	
	/* test7 */
	res = SLLIsEmpty(sll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	SLLErase(sll,iter1);
	
	/* test7 */
	res = SLLIsEmpty(sll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	SLLDestroy(sll);
	
	return result;
}

int Test_SLLFind(void)
{
	int result = 1;
	char res = 0;
	char expect = 0;
	/*it_t res2 = 0;
	it_t expect2 = 0;*/
	size_t test_no = 0;
	char c = 'a';
	char d = 'h';
	char e = 's';
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;
	it_t iter3 = NULL;
	sll_t *sll = SLLCreate();

	iter1 = SLLPushBack(sll, (void*)&c);
	n = *((char *)SLLGetData((void *)iter1));
	
	/* test1 */
	res = n;
	expect = 'a';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test2 */
	res = SLLSize(sll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	iter2 = SLLPushBack(sll, (void*)&d);
	n = *((char *)SLLGetData((void *)iter2));
	

	/* test3 */
	res = n;
	expect = 'h';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test4 */
	res = SLLSize(sll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	iter3 = SLLPushBack(sll, (void*)&e);
	n = *((char *)SLLGetData((void *)iter3));
	
	/* test4 */
	res = SLLSize(sll);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test5 */
	res = n;
	expect = 's';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	

	/* test7 
	res2 = SLLFind(SLLBegin(sll), SLLEnd(sll), (void *)&s2, charcmp);
	expect2 = SLLNext(iter1);
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	*/
	SLLDestroy(sll);
	
	return result;
}

int charcmp(const void *a, const void *b)
{
	if (*((char *)a) == *((char *)b))
	{
		return 1;
	}
	return 0;
}

int Test_SLLForEach(void)
{
	int result = 1;
	char res = 0;
	char expect = 0;
	size_t test_no = 0;
	char c = 'a';
	char d = 'h';
	char e = 's';
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;
	it_t iter3 = NULL;
	sll_t *sll = SLLCreate();

	iter1 = SLLPushBack(sll, (void*)&c);
	n = *((char *)SLLGetData((void *)iter1));
	
	/* test1 */
	res = n;
	expect = 'a';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test2 */
	res = SLLSize(sll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	iter2 = SLLPushBack(sll, (void*)&d);
	n = *((char *)SLLGetData((void *)iter2));
	

	/* test3 */
	res = n;
	expect = 'h';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test4 */
	res = SLLSize(sll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	iter3 = SLLPushBack(sll, (void*)&e);
	n = *((char *)SLLGetData((void *)iter3));
	
	/* test5 */
	res = SLLSize(sll);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test6 */
	res = n;
	expect = 's';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	

	/* test7 */
	printf("\t");
	res = SLLForEach(SLLBegin(sll), SLLEnd(sll), sll, print_list);
	printf("NULL\n");
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	SLLDestroy(sll);
	
	return result;
}

int print_list(void *data, const void *arg)
{
	UNUSED(arg);
    printf("%c->", *(char *)data);   
    return 0;
}

int Test_SLLFlip(void)
{
	int result = 1;
	char res = 0;
	char expect = 0;
	size_t test_no = 0;
	char c = 'a';
	char d = 'h';
	char e = 's';
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;
	it_t iter3 = NULL;
	sll_t *sll = SLLCreate();

	iter1 = SLLPushBack(sll, (void*)&c);
	n = *((char *)SLLGetData((void *)iter1));
	
	/* test1 */
	res = n;
	expect = 'a';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	
	iter2 = SLLPushBack(sll, (void*)&d);
	n = *((char *)SLLGetData((void *)iter2));
	
	/* test3 */
	res = n;
	expect = 'h';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);

	iter3 = SLLPushBack(sll, (void*)&e);
	n = *((char *)SLLGetData((void *)iter3));
	
	/* test5 */
	res = SLLSize(sll);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test6 */
	res = n;
	expect = 's';
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect, res);
	result *= (expect == res);
	

	/* test7 */
	printf("\t");
	res = SLLForEach(SLLBegin(sll), SLLEnd(sll), SLLFLip(sll), print_list);
	printf("NULL\n");
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	SLLDestroy(sll);
	
	return result;
}
