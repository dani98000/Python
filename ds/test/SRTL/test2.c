/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 10/06/19                                *
*   Description: Sorted list Unit test file       *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */

#include "tests.h" /* test macros */
#include "../../include/SRTL/srtl.h"

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

int Test_CreateDestroy(void);
int Test_Flow(void);
int Test_Merge(void);

int IntCompare(const void *data, const void *new_data, 
	const void *params);
static void PrintSrtL(srtl_t *list);
int FindInt(const void *data, const void *key, const void *params);

enum order
{
	ASCENDING,
	DESCENDING
};

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	RUN_TEST(Test_CreateDestroy);
	RUN_TEST(Test_Flow);
	RUN_TEST(Test_Merge);

	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	

	return 0;
}

int IntCompare(const void *data, const void *new_data, 
	const void *params)
{
	if(ASCENDING == *(enum order*)params)
	{
		return (*(int *)new_data < *(int *)data) ? 1 : 0;
	}
	else
	{
		return (*(int *)new_data > *(int *)data) ? 1 : 0;
	}
}

int Test_CreateDestroy(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	srtl_t *list = NULL;
	enum order my_order = ASCENDING;
	
	puts("\x1B[33m[Test_CreateDestroy]\033[0m");

	list = SrtLCreate(IntCompare, &my_order);
	
	TEST_EQUAL(res, 0);

	SrtLDestroy(list);

	return result;
}

int Test_Flow(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	srtl_t *list = NULL;
	enum order my_order = ASCENDING;
	int data[5] = {4, 2, 3, 5, 1};
	sit_t itr = NULL;
	
	puts("\x1B[33m[Test_Flow]\033[0m");

	list = SrtLCreate(IntCompare, &my_order);
	
	/* test1 */
	res = (int)SrtLSize(list);
	TEST_EQUAL(res, 0);
	
	
	/* test2 */
	res = (int)SrtLIsEmpty(list);
	TEST_EQUAL(res, 1);
	
	SrtLInsert(list, data);

	/* test3 */
	res = (int)SrtLSize(list);
	TEST_EQUAL(res, 1);
	
	
	/* test4 */
	res = (int)SrtLIsEmpty(list);
	TEST_EQUAL(res, 0);
	
	
	SrtLInsert(list, data + 1);
	SrtLInsert(list, data + 2);
	SrtLInsert(list, data + 3);
	SrtLInsert(list, data + 4);
	PrintSrtL(list);
	
	/* test5 */
	res = (int)SrtLSize(list);
	TEST_EQUAL(res, 5);
		
	/* test6 */
	itr = SrtLBegin(list);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 1);
	
	/* test7 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	/* test8 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 3);
	
	/* test9 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 4);
	
	/* test10 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 5);

	SrtLDestroy(list);
	
	my_order = DESCENDING;
	list = SrtLCreate(IntCompare, &my_order);
	
	SrtLInsert(list, data);	
	SrtLInsert(list, data + 1);
	SrtLInsert(list, data + 2);
	SrtLInsert(list, data + 3);
	SrtLInsert(list, data + 4);
	PrintSrtL(list);
		
	/* test11 */
	itr = SrtLBegin(list);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 5);
	
	/* test12 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 4);
	
	/* test13 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 3);
	
	/* test14 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	/* test15 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 1);

	SrtLPopFront(list);
	SrtLPopBack(list);
	PrintSrtL(list);
	
	/* test16 */
	itr = SrtLBegin(list);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 4);
	
	/* test17 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 3);
	
	/* test18 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	/* test19 */
	itr = SrtLFind(SrtLBegin(list), SrtLEnd(list), FindInt, data + 2, NULL);
	res = SrtLIsSame(itr, SrtLEnd(list));
	TEST_EQUAL(res, 0);
	
	/* test20 */
	itr = SrtLFind(SrtLBegin(list), SrtLEnd(list), FindInt, data + 3, NULL);
	res = SrtLIsSame(itr, SrtLEnd(list));
	TEST_EQUAL(res, 1);

	SrtLDestroy(list);

	return result;
}

int Test_Merge(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	srtl_t *list1 = NULL;
	srtl_t *list2 = NULL;
	enum order my_order = ASCENDING;
	int data1[4] = {1, 3, 4, 7};
	int data2[7] = {2, 2, 5, 6, 8, 9, 10};
	sit_t itr = NULL;
	
	puts("\x1B[33m[Test_Merge]\033[0m");

	list1 = SrtLCreate(IntCompare, &my_order);
	list2 = SrtLCreate(IntCompare, &my_order);
	
	/* fill list1 */
	SrtLInsert(list1, data1);
	SrtLInsert(list1, data1 + 1);
	SrtLInsert(list1, data1 + 2);
	SrtLInsert(list1, data1 + 3);
	
	/* fill list2 */
	SrtLInsert(list2, data2);
	SrtLInsert(list2, data2 + 1);
	SrtLInsert(list2, data2 + 2);
	SrtLInsert(list2, data2 + 3);
	SrtLInsert(list2, data2 + 4);
	SrtLInsert(list2, data2 + 5);
	SrtLInsert(list2, data2 + 6);

	puts("\tbefore merge:");
	printf("\tlist1: "); PrintSrtL(list1);
	printf("\tlist2: "); PrintSrtL(list2);

	SrtLMerge(list1, list2);
	
	puts("\tafter merge:");
	printf("\tlist1: "); PrintSrtL(list1);
	printf("\tlist2: "); PrintSrtL(list2);
	
	/* test1 */
	res = SrtLIsEmpty(list2);
	TEST_EQUAL(res, 1);
	
	
	/* test2 */
	itr = SrtLBegin(list1);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 1);
	
	/* test3 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	/* test4 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	/* test5 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 3);
	
	/* test6 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 4);
	
	/* test7 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 5);
	
	/* test8 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 6);
	
	/* test9 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 7);
	
	/* test10 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 8);
	
	/* test11 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 9);
	
	/* test12 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 10);
	
	puts("\tafter merge:");
	printf("\tlist1: "); PrintSrtL(list1);
	printf("\tlist2: "); PrintSrtL(list2);

	SrtLDestroy(list1);
	SrtLDestroy(list2);

	list1 = SrtLCreate(IntCompare, &my_order);
	list2 = SrtLCreate(IntCompare, &my_order);
	
	/* fill list1 */
	SrtLInsert(list1, data1);
	
	/* fill list2 */
	SrtLInsert(list2, data2);
	SrtLInsert(list2, data2 + 1);
	
	puts("\tbefore merge:");
	printf("\tlist1: "); PrintSrtL(list1);
	printf("\tlist2: "); PrintSrtL(list2);
	
	SrtLMerge(list1, list2);
	
	/* test13 */
	itr = SrtLBegin(list1);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 1);
	
	/* test14 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	/* test15 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	puts("\tafter merge:");
	printf("\tlist1: "); PrintSrtL(list1);
	printf("\tlist2: "); PrintSrtL(list2);

	SrtLDestroy(list1);
	SrtLDestroy(list2);
	
	list1 = SrtLCreate(IntCompare, &my_order);
	list2 = SrtLCreate(IntCompare, &my_order);
	
	/* fill list1 */
	SrtLInsert(list1, data2);
	
	/* fill list2 */
	SrtLInsert(list2, data1);
	SrtLInsert(list2, data2 + 1);
	
	puts("\tbefore merge:");
	printf("\tlist1: "); PrintSrtL(list1);
	printf("\tlist2: "); PrintSrtL(list2);
	
	SrtLMerge(list1, list2);

	/* test16 */
	itr = SrtLBegin(list1);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 1);
	
	/* test17 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	/* test18 */
	itr = SrtLNext(itr);
	res = *(int *)SrtLGetData(itr);
	TEST_EQUAL(res, 2);
	
	puts("\tafter merge:");
	printf("\tlist1: "); PrintSrtL(list1);
	printf("\tlist2: "); PrintSrtL(list2);
	
	SrtLDestroy(list1);
	SrtLDestroy(list2);

	return result;
}

static void PrintSrtL(srtl_t *list)
{
	sit_t cur = SrtLBegin(list);
	printf("\t[h]->");
	for(; cur != SrtLEnd(list); cur = SrtLNext(cur))
	{
		printf("%d->", *(int *)SrtLGetData(cur));
	}
	printf("[t]\n");
}

int FindInt(const void *data, const void *key, const void *params)
{
	(void)params;
	return (*(int *)key == *(int *)data) ? 1 : 0;
}




















