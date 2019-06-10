#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "../../include/DLL/dll.h"

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

int Test_DLLPushBack(void);
int Test_DLLPushFront(void);
int Test_DLLPopFront(void);
int Test_DLLPopBack(void);
int Test_DLLInsert();
int charcmp(const void *a, const void *b);
int Test_DLLFind(void);
int print_list(void *data, const void *arg);
int Test_DLLForEach(void);
int Test_SpliceBefore();

int main()
{
	RUN_TEST(Test_DLLPushBack);
	RUN_TEST(Test_DLLPushFront);	
	RUN_TEST(Test_DLLPopFront);	
	RUN_TEST(Test_DLLPopBack);	
	RUN_TEST(Test_DLLInsert);	
	RUN_TEST(Test_DLLFind);
	RUN_TEST(Test_DLLForEach);
	RUN_TEST(Test_SpliceBefore);
	
	
	
	return 0;
}

int Test_DLLPushBack(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 5;
	int d = 8;
	char n = 0;
	it_t iter1 = NULL;
	dll_t *dll = DLLCreate();
	
	/* test1 */
	res = DLLSize(dll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = DLLPushFront(dll, (void*)&c);
	n = *((int *)DLLGetData((void *)iter1));

	/* test2 */
	res = n;
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	
	/* test3 */
	res = DLLSize(dll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = DLLPushFront(dll, (void*)&d);
	n = *((int *)DLLGetData((void *)iter1));

	/* test4 */
	res = n;
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((int *)DLLGetData(DLLBegin(dll)));
	
	/* test7 */
	res = n;
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test8 */
	res = DLLSize(dll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DLLDestroy(dll);

	return result;
}

int Test_DLLPushFront(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 1;
	int d = 2;
	int e = 3;
	char n = 0;
	dll_t *dll = DLLCreate();
	
	/* test1 */
	res = DLLSize(dll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLPushFront(dll, (void*)&c);
	DLLPushFront(dll, (void*)&d);
	DLLPushFront(dll, (void*)&e);
	
	
	/* test2 */
	res = DLLSize(dll);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((int *)DLLGetData(DLLBegin(dll)));
	
	/* test3 */
	res = n;
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((int *)DLLGetData(DLLNext(DLLBegin(dll))));
	
	/* test4 */
	res = n;
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((int *)DLLGetData(DLLPrev(DLLEnd(dll))));
	
	/* test5 */
	res = n;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLErase(DLLBegin(dll));
	
	/* test6 */
	res = DLLSize(dll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((int *)DLLGetData(DLLBegin(dll)));
	
	/* test7 */
	res = n;
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLDestroy(dll);

	return result;
}

int Test_DLLPopFront(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 1;
	int d = 2;
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;
	dll_t *dll = DLLCreate();
	
	/* test1 */
	res = DLLSize(dll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = DLLPushBack(dll, (void*)&c);
	n = *((int *)DLLGetData((void *)iter1));

	/* test2 */
	res = n;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	iter2 = DLLPushBack(dll, (void*)&d);
	n = *((int *)DLLGetData((void *)iter2));

	/* test3 */
	res = n;
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test4 */
	res = DLLSize(dll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLPopFront(dll);
	
	/* test5 */
	res = DLLSize(dll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((char *)DLLGetData(DLLBegin(dll)));
	
	/* test6 */
	res = n;
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	
	
	/* test7 */
	res = DLLIsEmpty(dll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLPopFront(dll);
	
	/* test8 */
	res = DLLIsEmpty(dll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DLLDestroy(dll);
	
	return result;
}


int Test_DLLPopBack(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 1;
	int d = 2;
	char n = 0;
	it_t iter1 = NULL;
	it_t iter2 = NULL;
	dll_t *dll = DLLCreate();
	
	/* test1 */
	res = DLLSize(dll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = DLLPushBack(dll, (void*)&c);
	n = *((int *)DLLGetData((void *)iter1));

	/* test2 */
	res = n;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	iter2 = DLLPushBack(dll, (void*)&d);
	n = *((int *)DLLGetData((void *)iter2));

	/* test3 */
	res = n;
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test4 */
	res = DLLSize(dll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLPopBack(dll);
	
	/* test5 */
	res = DLLSize(dll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((char *)DLLGetData(DLLBegin(dll)));
	
	/* test6 */
	res = n;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	
	
	/* test7 */
	res = DLLIsEmpty(dll);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLPopFront(dll);
	
	/* test8 */
	res = DLLIsEmpty(dll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DLLDestroy(dll);
	
	return result;
}

int Test_DLLInsert()
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int c = 1;
	int d = 2;
	char n = 0;
	it_t iter1 = NULL;
	dll_t *dll = DLLCreate();
	DLLPushBack(dll, (void*)&d);
	
	/* test1 */
	res = DLLSize(dll);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	iter1 = DLLInsert(dll, DLLBegin(dll), (void*)&c);
	n = *((int *)DLLGetData((void *)iter1));
	
	/* test2 */
	res = DLLSize(dll);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	n = *((char *)DLLGetData(DLLBegin(dll)));
	
	/* test6 */
	res = n;
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLDestroy(dll);
	
	return result;
	
}

int Test_DLLFind(void)
{
	int result = 1;
	char res = 0;
	it_t res2 = 0;
	char expect = 0;
	char expect2 = 0;
	size_t test_no = 0;
	char c = 'a';
	char d = 'h';
	char e = 's';
	char n = 0;
	char s2 = 'h';
	it_t iter1 = NULL;
	it_t iter2 = NULL;
	it_t iter3 = NULL;
	dll_t *dll = DLLCreate();
	UNUSED(iter2);
	UNUSED(iter3);

	iter1 = DLLPushBack(dll, (void*)&c);
	iter2 = DLLPushBack(dll, (void*)&d);
	iter3 = DLLPushBack(dll, (void*)&e);;
	
	/* test1 */
	res = DLLSize(dll);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	

	/* test7 */
	res2 = DLLFind(DLLBegin(dll), DLLEnd(dll), charcmp, NULL, (void *)&s2);
	n = *((char *)DLLGetData(res2));
	expect2 = *((char *)DLLGetData(DLLNext(iter1)));
	++test_no;
	printf("\ttest %lu: expected: %c, got: %c\n", test_no, expect2, n);
	result *= (expect == res);
	
	DLLDestroy(dll);
	
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

int Test_DLLForEach(void)
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int a = 1;
	int b = 2;
	int c = 3;

	dll_t *dll = DLLCreate();

	DLLPushBack(dll, (void*)&a);
	DLLPushBack(dll, (void*)&b);
	DLLPushBack(dll, (void*)&c);;
	
	/* test1 */
	res = DLLSize(dll);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	

	/* test7 */
	printf("\t");
	res = DLLForEach(DLLBegin(dll), DLLEnd(dll), print_list, dll);
	printf("NULL\n");
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLDestroy(dll);
	
	return result;
}

int print_list(void *data, const void *arg)
{
	UNUSED(arg);
    printf("%d->", *(char *)data);   
    return 0;
}

int Test_SpliceBefore()
{
	int result = 1;
	int res = 0;
	int expect = 0;
	size_t test_no = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	int g = 7;
	
	it_t where = NULL;
	it_t from = NULL;
	it_t to = NULL;

	dll_t *dll1 = DLLCreate();
	dll_t *dll2 = DLLCreate();

	DLLPushBack(dll1, (void*)&a);
	where = DLLPushBack(dll1, (void*)&b);
	DLLPushBack(dll1, (void*)&c);
	
	DLLPushBack(dll2, (void*)&d);
	from = DLLPushBack(dll2, (void*)&e);
	DLLPushBack(dll2, (void*)&f);
	to = DLLPushBack(dll2, (void*)&g);
	
	/* test1 */ 
	res = DLLSize(dll1);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	/* test2 */ 
	res = DLLSize(dll2);
	expect = 4;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	res = *((int *)DLLGetData(DLLSpliceBefore(where,from,to)));
	printf("\t");
	DLLForEach(DLLBegin(dll2), DLLEnd(dll2), print_list, dll2);
	printf("NULL\n");
		
	printf("\t");
	DLLForEach(DLLBegin(dll1), DLLEnd(dll1), print_list, dll1);
	printf("NULL\n");
	
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DLLDestroy(dll1);
	DLLDestroy(dll2);
	
	return result;
}
