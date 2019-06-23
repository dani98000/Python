/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 21/06/19                                *
*   Description:     *
*                                                 *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* memset */

#include "tests.h" /* test macros */
#include "vsma.h"

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

int Test_Init(void);
int Test_CountFree(void);
int Test_LargestFree(void);
int Test_Free(void);
int Test_Alloc(void);

int Test_DInit(void);
int Test_DCountFree(void);
int Test_DLargestFree(void);
int Test_DFree(void);
int Test_DAlloc(void);

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	#ifdef NDEBUG
	RUN_TEST(Test_Init);
	RUN_TEST(Test_CountFree);
	RUN_TEST(Test_LargestFree);
	RUN_TEST(Test_Free);
	RUN_TEST(Test_Alloc);
	#else
	RUN_TEST(Test_DInit);
	RUN_TEST(Test_DCountFree);
	RUN_TEST(Test_DLargestFree);
	RUN_TEST(Test_DFree);
	RUN_TEST(Test_DAlloc);
	#endif

	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	

	return 0;
}

int Test_Init(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	
	puts("\x1B[33m[Test_Init]\033[0m");

	pool = malloc(pool_size);
	vsma = VSMAInit(pool, pool_size);

	/* test1 */
	res = ((int)*(long *)vsma);
	TEST_EQUAL(res, 480);

	free(pool);
	return result;
}

int Test_DInit(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	
	puts("\x1B[33m[Test_Init]\033[0m");

	pool = malloc(pool_size);
	vsma = VSMAInit(pool, pool_size);

	/* test1 */
	res = ((int)*(long *)vsma);
	TEST_EQUAL(res, 464);

	free(pool);
	return result;
}

int Test_CountFree(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	void *block = NULL;

	puts("\x1B[33m[Test_CountFree]\033[0m");

	pool = malloc(pool_size);

	/* to prevent lucky zeros */
	memset(pool, 0x1, pool_size);

	vsma = VSMAInit(pool, pool_size);

	/* test1 */
	res = ((int)VSMACount(vsma));
	TEST_EQUAL(res, 480);

	/* test2 */
	block = VSMAAlloc(vsma, 1);
	res = ((int)VSMACount(vsma));
	TEST_EQUAL(res, 464);

	/* test3 */
	VSMAAlloc(vsma, 1);
	res = ((int)VSMACount(vsma));
	TEST_EQUAL(res, 448);

	VSMAFree(block);
	
	/* test4 */
	res = ((int)VSMACount(vsma));
	TEST_EQUAL(res, 456);

	free(pool);
	return result;
}

int Test_DCountFree(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	void *block = NULL;
	
	puts("\x1B[33m[Test_CountFree]\033[0m");

	pool = malloc(pool_size);

	/* to prevent lucky zeros */
	memset(pool, 0x1, pool_size);

	vsma = VSMAInit(pool, pool_size);

	/* test1 */
	res = ((int)VSMACount(vsma));
	TEST_EQUAL(res, 464);

	/* test2 */
	block = VSMAAlloc(vsma, 1);
	res = ((int)VSMACount(vsma));
	TEST_EQUAL(res, 440);

	/* test3 */
	VSMAAlloc(vsma, 1);
	res = ((int)VSMACount(vsma));
	TEST_EQUAL(res, 416);

	VSMAFree(block);
	
	/* test4 */
	res = ((int)VSMACount(vsma));
	TEST_EQUAL(res, 424);

	free(pool);
	return result;
}

int Test_LargestFree(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	void *block1 = NULL, *block2 = NULL;
	
	puts("\x1B[33m[Test_LargestFree]\033[0m");

	pool = malloc(pool_size);

	/* to prevent lucky zeros */
	memset(pool, 0x1, pool_size);

	vsma = VSMAInit(pool, pool_size);

	/* test1 */
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 480);

	/* test2 */
	block1 = VSMAAlloc(vsma, 50); /* will allocate 56 */
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 416);

	/* test3 */
	block2 = VSMAAlloc(vsma, 50); /* will allocate 56 */
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 352);
	
	/* test4 */
	VSMAFree(block1);
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 352);

	/* test5 */
	VSMAFree(block2);
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 480);

	free(pool);
	return result;
}

int Test_DLargestFree(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	void *block1 = NULL, *block2 = NULL;
	
	puts("\x1B[33m[Test_LargestFree]\033[0m");

	pool = malloc(pool_size);

	/* to prevent lucky zeros */
	memset(pool, 0x1, pool_size);

	vsma = VSMAInit(pool, pool_size);

	/* test1 */
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 464);

	/* test2 */
	block1 = VSMAAlloc(vsma, 50); /* will allocate 56 */
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 392);

	/* test3 */
	block2 = VSMAAlloc(vsma, 50); /* will allocate 56 */
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 320);
	
	/* test4 */
	VSMAFree(block1);
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 320);

	/* test5 */
	VSMAFree(block2);
	res = ((int)VSMAFindLargestFree(vsma));
	TEST_EQUAL(res, 464);

	free(pool);
	return result;
}

int Test_Free(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	void *block1 = NULL, *block2 = NULL;	
	void *block3 = NULL, *block4 = NULL;	

	puts("\x1B[33m[Test_Free]\033[0m");

	pool = malloc(pool_size);

	/* to prevent lucky zeros */
	memset(pool, 0x1, pool_size);

	vsma = VSMAInit(pool, pool_size);
	
	/* test1 */
	block1 = VSMAAlloc(vsma, 480);
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 0);

	/* test2 */
	VSMAFree(block1);
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 480);

	/* test3 */
	block1 = VSMAAlloc(vsma, 300); /* will allocate 304 bytes */
	res = (int)VSMAFindLargestFree(vsma);
	block2 = VSMAAlloc(vsma, res);
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 0);

	/* test4 */
	VSMAFree(block1);
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 304);

	/* test5 */
	VSMAFree(block2);
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 480);

	/* test6 */
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 480);

	block1 = VSMAAlloc(vsma, 10);
	block2 = VSMAAlloc(vsma, 10);
	block3 = VSMAAlloc(vsma, 10);
	block4 = VSMAAlloc(vsma, 10);

	/* test7 */
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 384);

	VSMAFree(block1);
	VSMAFree(block3);

	/* test8 */
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 416);

	VSMAFree(block2);
	VSMAFree(block4);

	/* test9 */
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 480);

	free(pool);
	return result;
}

int Test_DFree(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	void *block1 = NULL, *block2 = NULL;	
	void *block3 = NULL, *block4 = NULL;	

	puts("\x1B[33m[Test_Free]\033[0m");

	pool = malloc(pool_size);

	/* to prevent lucky zeros */
	memset(pool, 0x1, pool_size);

	vsma = VSMAInit(pool, pool_size);
	
	/* test1 */
	block1 = VSMAAlloc(vsma, 464);
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 0);

	/* test2 */
	VSMAFree(block1);
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 464);

	/* test3 */
	block1 = VSMAAlloc(vsma, 300); /* will allocate 304 bytes */
	res = (int)VSMAFindLargestFree(vsma);
	block2 = VSMAAlloc(vsma, res);
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 0);

	/* test4 */
	VSMAFree(block1);
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 304);

	/* test5 */
	VSMAFree(block2);
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 464);

	/* test6 */
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 464);

	block1 = VSMAAlloc(vsma, 10);
	block2 = VSMAAlloc(vsma, 10);
	block3 = VSMAAlloc(vsma, 10);
	block4 = VSMAAlloc(vsma, 10);

	/* test7 */
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 336);

	VSMAFree(block1);
	VSMAFree(block3);

	/* test8 */
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 368);

	VSMAFree(block2);
	VSMAFree(block4);

	/* test9 */
	res = (int)VSMACount(vsma);
	TEST_EQUAL(res, 464);

	free(pool);
	return result;
}

int Test_Alloc(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	void *block1, *block2, *block3, *block4;

	block1 = block2 = block3 = block4 = NULL;
	
	puts("\x1B[33m[Test_Alloc]\033[0m");

	pool = malloc(pool_size);

	/* to prevent lucky zeros */
	memset(pool, 0x1, pool_size);

	vsma = VSMAInit(pool, pool_size);

	(void)block1;	
	
	/* test1 */
	block1 = VSMAAlloc(vsma, 100); /* will allocate 104 */
	block2 = VSMAAlloc(vsma, 100); /* will allocate 104 */
	block3 = VSMAAlloc(vsma, 100); /* will allocate 104 */
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 144);

	/* test2 */
	block4 = VSMAAlloc(vsma, 100);  /* will allocate 104 */
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 32);

	/* test3 */
	VSMAFree(block2);
	VSMAFree(block3);
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 216);
	
	/* test4 */
	block2 = VSMAAlloc(vsma, 300); /* should return NULL */
	res = NULL == block2;
	TEST_EQUAL(res, 1);

	/* test5 */
	block2 = VSMAAlloc(vsma, 216);
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 32);

	free(pool);
	return result;
}

int Test_DAlloc(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	void *pool = NULL;
	vsma_t *vsma = NULL;
	size_t pool_size = 500;
	void *block1, *block2, *block3, *block4;

	block1 = block2 = block3 = block4 = NULL;
	
	puts("\x1B[33m[Test_Alloc]\033[0m");

	pool = malloc(pool_size);

	/* to prevent lucky zeros */
	memset(pool, 0x1, pool_size);

	vsma = VSMAInit(pool, pool_size);	
	
	(void)block1;

	/* test1 */
	block1 = VSMAAlloc(vsma, 100); /* will allocate 104 */
	block2 = VSMAAlloc(vsma, 100); /* will allocate 104 */
	block3 = VSMAAlloc(vsma, 100); /* will allocate 104 */
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 104);

	/* test2 */
	block4 = VSMAAlloc(vsma, 100);  /* will allocate 104 */
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 0);

	/* test3 */
	VSMAFree(block2);
	VSMAFree(block3);
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 224);
	
	/* test4 */
	block2 = VSMAAlloc(vsma, 300); /* should return NULL */
	res = NULL == block2;
	TEST_EQUAL(res, 1);

	/* test5 */
	block2 = VSMAAlloc(vsma, 224);
	res = (int)VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 0);
	
	free(pool);
	return result;
}


