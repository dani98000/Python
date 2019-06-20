#include <stdio.h>
#include <stdlib.h>

#include "fsma.h"

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


int Test_FSMASuggestSize();
int Test_FSMAInit();
int Test_FSMAAlloc();
int Test_FSMACountFree();

int main()
{
	RUN_TEST(Test_FSMASuggestSize);
	RUN_TEST(Test_FSMAInit);
	RUN_TEST(Test_FSMAAlloc);
	RUN_TEST(Test_FSMACountFree);
	
	return 0;
}

int Test_FSMASuggestSize()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	
	/* test 1 */
	res = FSMASuggestSize(5, 5);
	TEST_EQUAL(res, 104);
	
	/* test 2 */
	res = FSMASuggestSize(8, 8);
	TEST_EQUAL(res, 152);
	
	/* test 3 */
	res = FSMASuggestSize(8, 1);
	TEST_EQUAL(res, 152);

	/* test 4 */
	res = FSMASuggestSize(1, 8);
	TEST_EQUAL(res, 40);
	
	return result;
}

int Test_FSMAInit()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	fsma_t *pool = (fsma_t *)malloc(FSMASuggestSize(5,5));	
	pool = FSMAInit(pool, FSMASuggestSize(5,5), 5);	
	
	/* test 1 */
	res = FSMASuggestSize(5, 5);
	TEST_EQUAL(res, 104);
	
	/* test 2 */
	res = *(size_t *)((char *)pool);
	TEST_EQUAL(res, 24);
		
	/* test 3 */
	res = *(size_t *)((char *)pool + 8);
	TEST_EQUAL(res, 5);	
	
	/* test 4 */
	res = *(size_t *)((char *)pool + 16);
	TEST_EQUAL(res, 5);		
	
	/* test 5 */
	res = *(size_t *)((char *)pool + 24);
	TEST_EQUAL(res, 40);
			
	return result;
}

int Test_FSMAAlloc()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	size_t a = 5;
	fsma_t *pool = (fsma_t *)malloc(FSMASuggestSize(5,5));	
	pool = FSMAInit(pool, FSMASuggestSize(5,5), 5);	
	
	/* test 1 */
	res = FSMASuggestSize(5, 5);
	TEST_EQUAL(res, 104);

	pool = FSMAAlloc(pool);
	*(size_t *)pool	= a;	

	/* test 2 */	
	res = *(size_t *)((char *)pool - 8);
	TEST_EQUAL(res, 24);
	
	/* test 3 */
	res = *(size_t *)((char *)pool);
	TEST_EQUAL(res, 5);
	
	/* test 4 */	
	res = *(size_t *)((char *)pool - 8);
	TEST_EQUAL(res, 24);
	
	/* test 5 */	
	res = *(size_t *)((char *)pool + 8);
	TEST_EQUAL(res, 56);		
	
	return result;
}

int Test_FSMACountFree()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	size_t a = 5;
	size_t b = 8;
	fsma_t *pool = (fsma_t *)malloc(FSMASuggestSize(5,5));	
	fsma_t *temp = NULL;
	pool = FSMAInit(pool, FSMASuggestSize(5,5), 5);	
	
	/* test 1 */
	res = FSMASuggestSize(5, 5);
	TEST_EQUAL(res, 104);
	
	/* test 2 */	
	res = FSMACountFree(pool);
	TEST_EQUAL(res, 5);

	temp = FSMAAlloc(pool);
	*(size_t *)temp	= a;		

	/* test 3 */	
	res = FSMACountFree(pool);
	TEST_EQUAL(res, 4);
	
	FSMAAlloc(pool);
	
	/* test 4 */
	res = *(size_t *)((char *)temp);
	TEST_EQUAL(res, 5);	
	
	/* test 5 */	
	res = FSMACountFree(pool);
	TEST_EQUAL(res, 3);

	FSMAFree(temp);

	/* test 6 */	
	res = FSMACountFree(pool);
	TEST_EQUAL(res, 4);
	
	*(size_t *)temp	= b;
	
	/* test 7 */
	res = *(size_t *)((char *)temp);
	TEST_EQUAL(res, 8);		
	
		FSMAAlloc(pool);
		FSMAAlloc(pool);
		FSMAAlloc(pool);
		
	/* test 6 */	
	res = FSMACountFree(pool);
	TEST_EQUAL(res, 1);
	
	return result;
}
