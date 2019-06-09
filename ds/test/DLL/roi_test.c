/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 06/06/19                                *
*   Description: DLL Test file                    *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */

#include "tests.h" /* test macros */
#include "../../include/DLL/dll.h"

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

int Test_CreateDestroy(void);
int Test_IsEmpty(void);
int Test_Size(void);
int Test_Pushes(void);
int Test_Pops(void);
int Test_ForEach(void);
int Test_Find(void);
int Test_Splice(void);
int Test_Flip(void);

int IncrementData(void *itr, const void *num);
int FindFirstBigger(const void *data, const void *num);
void PrintDLL(dll_t *list);

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	RUN_TEST(Test_CreateDestroy);
	RUN_TEST(Test_IsEmpty);
	RUN_TEST(Test_Size);
	RUN_TEST(Test_Pushes);
	RUN_TEST(Test_Pops);
	RUN_TEST(Test_ForEach);
	RUN_TEST(Test_Find);
	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);

	return 0;
}

int Test_CreateDestroy(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	dll_t *list = NULL;
	
	puts("\x1B[33m[Test_CreateDestroy]\033[0m");
	
	list = DLLCreate();
	
	TEST_EQUAL(res, 0);

	DLLDestroy(list);

	return result;
}

int Test_IsEmpty(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	dll_t *list = NULL;
	int data = 1;
	
	puts("\x1B[33m[Test_IsEmpty]\033[0m");
	
	list = DLLCreate();
	
	/* test1 */
	res = DLLIsEmpty(list);
	TEST_EQUAL(res, 1);
	
	/* test2 */
	DLLPushBack(list, &data);
	res = DLLIsEmpty(list);
	TEST_EQUAL(res, 0);

	DLLDestroy(list);

	return result;
}

int Test_Size(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	dll_t *list = NULL;
	int data = 1;
	
	puts("\x1B[33m[Test_Size]\033[0m");
	
	list = DLLCreate();
	
	/* test1 */
	res = (int)DLLSize(list);
	TEST_EQUAL(res, 0);
	
	/* test2 */
	DLLPushBack(list, &data);
	res = (int)DLLSize(list);
	TEST_EQUAL(res, 1);
	
	/* test2 */
	DLLPushBack(list, &data);
	res = (int)DLLSize(list);
	TEST_EQUAL(res, 2);

	DLLDestroy(list);

	return result;
}

int Test_Pushes(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	dll_t *list = NULL;
	int data[] = {1, 2, 3, 4, 5};
	it_t itr = NULL;
	
	puts("\x1B[33m[Test_Pushes]\033[0m");
	
	list = DLLCreate();
	
	/* test1 */
	itr = DLLPushBack(list, &data[0]);
	res = DLLGetData(itr) == &data[0];
	TEST_EQUAL(res, 1);
	
	/* test2 */
	res = *(int *)DLLGetData(DLLPrev(DLLEnd(list)));
	TEST_EQUAL(res, data[0]);
	
	/* test2 */
	itr = DLLPushFront(list, &data[1]);
	res = DLLGetData(itr) == &data[1];
	TEST_EQUAL(res, 1);
	
	/* test3 */
	res = *(int *)DLLGetData(DLLBegin(list));
	TEST_EQUAL(res, data[1]);

	
	DLLDestroy(list);

	return result;
}

int Test_Pops(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	dll_t *list = NULL;
	int data[] = {1, 2, 3, 4, 5};
	it_t itr = NULL;
	
	puts("\x1B[33m[Test_Pops]\033[0m");
	
	list = DLLCreate();
	
	/* fill dll */
	DLLPushBack(list, &data[0]);
	DLLPushBack(list, &data[1]);
	DLLPushBack(list, &data[2]);
	DLLPushBack(list, &data[3]);
	DLLPushBack(list, &data[4]);
	
	/* test1 */
	DLLPopFront(list);
	itr = DLLBegin(list);
	res = *(int *)DLLGetData(itr);
	TEST_EQUAL(res, 2);

	/* test2 */
	DLLPopBack(list);
	itr = DLLPrev(DLLEnd(list));
	res = *(int *)DLLGetData(itr);
	TEST_EQUAL(res, 4);
	
	/* test3 */
	itr = DLLPrev(itr);
	itr = DLLErase(itr);
	res = *(int *)DLLGetData(itr);
	TEST_EQUAL(res, 4);
	
	/* test3 */
	itr = DLLPrev(itr);
	res = *(int *)DLLGetData(itr);
	TEST_EQUAL(res, 2);
	
	DLLDestroy(list);

	return result;
}

int Test_ForEach(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	dll_t *list = NULL;
	int data[] = {1, 2, 3, 4, 5};
	int num = 2;
	it_t itr = NULL;
	
	puts("\x1B[33m[Test_ForEach]\033[0m");
	
	list = DLLCreate();
	
	/* fill dll */
	DLLPushBack(list, &data[0]);
	DLLPushBack(list, &data[1]);
	DLLPushBack(list, &data[2]);
	DLLPushBack(list, &data[3]);
	DLLPushBack(list, &data[4]);
	
	PrintDLL(list);
	
	/* test1 */
	res = DLLForEach(DLLBegin(list), DLLEnd(list), IncrementData, &num);
	TEST_EQUAL(res, 1);
	
	PrintDLL(list);
	
	/* test1 */
	itr = DLLBegin(list);
	res = *(int *)DLLGetData(itr);
	TEST_EQUAL(res, 3);
	
	DLLDestroy(list);

	return result;
}

int Test_Find(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	dll_t *list = NULL;
	int data[] = {1, 2, 3, 4, 5};
	int num = 2;
	it_t itr = NULL;
	
	puts("\x1B[33m[Test_Find]\033[0m");
	
	list = DLLCreate();
	
	/* fill dll */
	DLLPushBack(list, &data[0]);
	DLLPushBack(list, &data[1]);
	DLLPushBack(list, &data[2]);
	DLLPushBack(list, &data[3]);
	DLLPushBack(list, &data[4]);
	
	PrintDLL(list);
	
	/* test1 */
	itr = DLLFind(DLLBegin(list), DLLEnd(list), FindFirstBigger, NULL, &num);
	res = *(int *)DLLGetData(itr);
	TEST_EQUAL(res, 3);
	
	DLLPopBack(list);
	DLLPopBack(list);
	DLLPopBack(list);
	
	PrintDLL(list);
	
	/* test2 */
	itr = DLLFind(DLLBegin(list), DLLEnd(list), FindFirstBigger, NULL, &num);
	res = itr == DLLEnd(list);
	TEST_EQUAL(res, 1);
	
	DLLDestroy(list);

	return result;
}



int IncrementData(void *data, const void* arg)
{
	int *p = (int *)data;
	
	if(*p + *(int *)arg < 6)
	{
		*p += *(int *)arg;
	}
	else
	{
		return 1;
	}
	
	return 0;
}

int FindFirstBigger(const void *data, const void *num)
{
	if(*(int *)data > *(int *)num)
	{
		return 1;
	}
	
	return 0;
}

void PrintDLL(dll_t *list)
{
	it_t cur = DLLBegin(list);
	printf("\t[h]->");
	for(; cur != DLLEnd(list); cur = DLLNext(cur))
	{
		printf("%d->", *(int *)DLLGetData(cur));
	}
	printf("[t]\n");
}































