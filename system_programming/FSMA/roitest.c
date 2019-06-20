/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 19/06/19                                *
*   Description:  FSMA Tests file                 *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#include "tests.h" /* test macros */
#include "fsma.h" /* fsma header file */

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

int Test_SuggestSize(void);
int Test_Init(void);
int Test_Alloc(void);
int Test_Free(void);
int Test_CountFree(void);
int Test_UseTest(void);

typedef struct doggie
{
	int age;
	int color;
	int weight;
} doggie_t;

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	RUN_TEST(Test_SuggestSize);
	RUN_TEST(Test_Init);
	RUN_TEST(Test_Alloc);
	RUN_TEST(Test_CountFree);
	RUN_TEST(Test_Free);
	RUN_TEST(Test_UseTest);

	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);

	return 0;
}

int Test_SuggestSize(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	
	puts("\x1B[33m[Test_SuggestSize]\033[0m");

	/* test1 */
	res = (int)FSMASuggestSize(3, 12);
	TEST_EQUAL(res, 96);
	
	/* test2 */
	res = (int)FSMASuggestSize(3, 8);
	TEST_EQUAL(res, 72);
	
	/* test3 */
	res = (int)FSMASuggestSize(7, 21);
	TEST_EQUAL(res, 248);

	return result;
}

int Test_Init(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool;
	fsma_t *fsma = NULL;
	
	puts("\x1B[33m[Test_Init]\033[0m");

	pool = malloc(FSMASuggestSize(3, 12));
	fsma = FSMAInit(pool, FSMASuggestSize(3, 12), 12);
	(void)fsma;
	/* test1 */
	TEST_EQUAL(res, 0);
	
	free(pool);	

	return result;
}

int Test_Alloc(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	void *data = NULL;
	fsma_t *fsma = NULL;
	
	puts("\x1B[33m[Test_Alloc]\033[0m");

	pool = malloc(FSMASuggestSize(3, 12));
	fsma = FSMAInit(pool, FSMASuggestSize(3, 12), 12);
	
	/* test1 */
	data = FSMAAlloc(fsma);
	res = (data != NULL);
	TEST_EQUAL(res, 1);
	
	/* test2 */
	data = FSMAAlloc(fsma);
	res = (data != NULL);
	TEST_EQUAL(res, 1);
	
	/* test3 */
	data = FSMAAlloc(fsma);
	res = (data != NULL);
	TEST_EQUAL(res, 1);
	
	/* test4 - this is white-box testing */ 
	data = FSMAAlloc(fsma);
	res = (data == ((size_t *)fsma + 1));
	TEST_EQUAL(res, 1);
	
	free(pool);	

	return result;
}

int Test_Free(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	void *data1 = NULL;
	void *data2 = NULL;
	void *data3 = NULL;
	fsma_t *fsma = NULL;
	
	puts("\x1B[33m[Test_Free]\033[0m");

	pool = malloc(FSMASuggestSize(3, 12));
	fsma = FSMAInit(pool, FSMASuggestSize(3, 12), 12);
	
	data1 = FSMAAlloc(fsma);
	data2 = FSMAAlloc(fsma);
	data3 = FSMAAlloc(fsma);
	
	/* test1 */
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 0);
	
	/* test2 */
	FSMAFree(data1);
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 1);
	
	/* test3 */
	FSMAFree(data2);
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 2);
	
	/* test4 */
	FSMAFree(data3);
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 3);
	
	free(pool);	

	return result;
}

int Test_CountFree(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	void *data = NULL;
	fsma_t *fsma = NULL;
	
	puts("\x1B[33m[Test_CountFree]\033[0m");

	pool = malloc(FSMASuggestSize(3, 12));
	fsma = FSMAInit(pool, FSMASuggestSize(3, 12), 12);
	(void)data;
	
	/* test1 */
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 3);
	
	/* test2 */
	data = FSMAAlloc(fsma);
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 2);
	
	/* test3 */
	data = FSMAAlloc(fsma);
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 1);
	
	/* test4 */
	data = FSMAAlloc(fsma);
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 0);
	
	free(pool);

	return result;
}

int Test_UseTest(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	
	doggie_t *dog1 = NULL, *dog2 = NULL, *dog3 = NULL;
	fsma_t *fsma = NULL;
	
	puts("\x1B[33m[Test_UseTest]\033[0m");

	pool = calloc(1, FSMASuggestSize(3, sizeof(doggie_t)));
	fsma = FSMAInit(pool, FSMASuggestSize(3, sizeof(doggie_t)), sizeof(doggie_t));
	
	dog1 = (doggie_t *)FSMAAlloc(fsma);
	dog1->age = 1;
	dog1->color = 2;
	dog1->weight = 3;
	dog2 = (doggie_t *)FSMAAlloc(fsma);
	dog2->age = 4;
	dog2->color = 5;
	dog2->weight = 6;
	dog3 = (doggie_t *)FSMAAlloc(fsma);
	dog3->age = 7;
	dog3->color = 8;
	dog3->weight = 9;
	
	/* test1 */
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 0);
	
	FSMAFree(dog1);
	FSMAFree(dog2);
	
	/* test2 */
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 2);
	
	dog1 = (doggie_t *)FSMAAlloc(fsma);
	dog1->age = 1;
	dog1->color = 2;
	dog1->weight = 10;
	
	/* test3 */
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 1);
	
	FSMAFree(dog3);
	FSMAFree(dog1);
	
	/* test4 */
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 3);
	
	dog1 = (doggie_t *)FSMAAlloc(fsma);
	dog1->age = 1;
	dog1->color = 2;
	dog1->weight = 3;
	dog2 = (doggie_t *)FSMAAlloc(fsma);
	dog2->age = 4;
	dog2->color = 5;
	dog2->weight = 6;
	dog3 = (doggie_t *)FSMAAlloc(fsma);
	dog3->age = 7;
	dog3->color = 8;
	dog3->weight = 9;
	
	/* test4 */
	res = (int)FSMACountFree(fsma);
	TEST_EQUAL(res, 0);
	
	free(pool);	

	return result;
}

















