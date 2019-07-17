#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "srtl.h"

#define UNUSED(X) (void) (X)

#define TEST_EQUAL(res, expected) \
printf("\ttest %lu: expected: %d, got: %d\n",\
++test_no, expected, res); result *= (expected == res); \

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
int is_before(const void *data, const void *key, const void *params);

int print_list(void *data, const void *arg)
{
	UNUSED(arg);
    printf("%d->", *(char *)data);   
    return 0;
}

int is_before(const void *data, const void *new_data, const void *params)
{
	UNUSED(params);
	return(*((int *)new_data) < *((int *)data));
}



int Test_SrtLInsert();
int Test_SrtLPops();
int Test_SrtLMerge();

int main()
{
	RUN_TEST(Test_SrtLInsert);
	RUN_TEST(Test_SrtLPops);
	RUN_TEST(Test_SrtLMerge);
		
	return 0;
}

int Test_SrtLInsert()
{
	srtl_t *srtl = NULL;
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	int a = 5;
	int b = 8;
	int c = 6;
	sit_t iter1 = NULL;
	
	srtl = SrtLCreate(is_before, NULL);
	
	
	/* test 1 */
	iter1 = SrtLInsert(srtl, &a);
	res = *((int *)SrtLGetData(iter1));
	TEST_EQUAL(res,5);
	
	/* test 2 */
	res = SrtLSize(srtl);
	TEST_EQUAL(res,1)
	
	/* test 3 */
	SrtLInsert(srtl, &b);
	SrtLInsert(srtl, &c);
	res = *((int *)SrtLGetData(SrtLPrev(SrtLEnd(srtl))));
	TEST_EQUAL(res,8);
	
	SrtLDestroy(srtl);
	
	return result;	
}

int Test_SrtLPops()
{
	srtl_t *srtl = NULL;
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	int a = 5;
	int b = 8;
	int c = 6;
	
	srtl = SrtLCreate(is_before, NULL);
	
	SrtLInsert(srtl, &a);
	SrtLInsert(srtl, &b);
	SrtLInsert(srtl, &c);
	
	/* test 1 */
	res = SrtLSize(srtl);
	TEST_EQUAL(res,3)
	
	/* test 2 */
	res = *((int *)SrtLGetData(SrtLPrev(SrtLEnd(srtl))));
	TEST_EQUAL(res,8)
	
	/* test 3 */
	SrtLPopBack(srtl);
	res = *((int *)SrtLGetData(SrtLPrev(SrtLEnd(srtl))));
	TEST_EQUAL(res,6)
	
	/* test 4 */
	SrtLPopFront(srtl);
	res = *((int *)SrtLGetData(SrtLPrev(SrtLEnd(srtl))));
	TEST_EQUAL(res,6);
	
	/* test 5 */
	res = SrtLSize(srtl);
	TEST_EQUAL(res,1)
	
	/* test 6 */
	res = SrtLIsEmpty(srtl);
	TEST_EQUAL(res,0);
	
	/* test 7 */
	SrtLErase(SrtLBegin(srtl));
	res = SrtLIsEmpty(srtl);
	TEST_EQUAL(res,1);
	

	SrtLDestroy(srtl);
	
	return result;	
}

int Test_SrtLMerge()
{
	srtl_t *dest = NULL;
	srtl_t *src = NULL;
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	
	int a = 1;
	int b = 3;
	int c = 4;
	int d = 7;
	int e = 2;
	int g = 5;
	int h = 6;
	int x = 8;
	int y = 9;
	int z = 10;			
	
	dest = SrtLCreate(is_before, NULL);
	src = SrtLCreate(is_before, NULL);
	
	SrtLInsert(dest, &a);
	SrtLInsert(dest, &b);
	SrtLInsert(dest, &c);
	SrtLInsert(dest, &d);

	SrtLInsert(src, &e);
	SrtLInsert(src, &e);
	SrtLInsert(src, &g);
	SrtLInsert(src, &h);
	SrtLInsert(src, &x);
	SrtLInsert(src, &y);
	SrtLInsert(src, &z);
	
	SrtLMerge(dest, src);
	printf("NULL->");
	SrtLForEach(SrtLBegin(dest), SrtLEnd(dest), print_list, dest);
	printf("NULL\n");
	printf("NULL->");
	SrtLForEach(SrtLBegin(src), SrtLEnd(src), print_list, src);
	printf("NULL\n");
	
	/* test 1 */
	res = SrtLIsEmpty(src);
	TEST_EQUAL(res,1);
	
	/* test 2 */
	res = SrtLSize(dest);
	TEST_EQUAL(res,11);
	
	/* test 3 */
	res = *((int *)SrtLGetData(SrtLBegin(dest)));
	TEST_EQUAL(res,1);
	
	/* test 4 */
	res = *((int *)SrtLGetData(SrtLPrev(SrtLEnd(dest))));
	TEST_EQUAL(res,10);
	
	SrtLDestroy(src);
	SrtLDestroy(dest);
	
	return result;	
}
