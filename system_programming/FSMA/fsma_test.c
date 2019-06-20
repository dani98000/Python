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

void test()
{
	size_t num_bytes = FSMASuggestSize(5, 5);
	
	fsma_t *pool = (fsma_t *)malloc(FSMASuggestSize(5,5));
	void *temp = NULL;
	printf("suggested size is: %lu\n", num_bytes);
	printf("metadata: %lu\n", *((size_t *)((char *)pool + 24)));
	
	temp = FSMAInit(pool, FSMASuggestSize(5,5), 5);
	printf("metadata: %lu\n", *((size_t *)((char *)pool + 24)));


	printf("Next free space: %lu\n", *((size_t *)((char *)pool)));
	printf("metadata: %lu\n", *((size_t *)((char *)pool + 24)));
	printf("there are %d free blocks\n",FSMACountFree(pool));	
	temp = FSMAAlloc(pool);		
	printf("there are %d free blocks\n",FSMACountFree(pool));	
	FSMAFree(temp);	
	printf("there are %d free blocks\n",FSMACountFree(pool));	
}

int Test_FSMASuggestSize();
int Test_FSMAInit();
int Test_FSMAAlloc();

int main()
{
	/*test();*/
	RUN_TEST(Test_FSMASuggestSize);
	RUN_TEST(Test_FSMAInit);
	RUN_TEST(Test_FSMAAlloc);
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
	fsma_t *pool = (fsma_t *)malloc(FSMASuggestSize(5,5));	
	pool = FSMAInit(pool, FSMASuggestSize(5,5), 5);	
	
	/* test 1 */
	res = FSMASuggestSize(5, 5);
	TEST_EQUAL(res, 104);

	pool = FSMAAlloc(pool);		

	/* test 3 */	
	res = *(size_t *)((char *)pool - 8);
	TEST_EQUAL(res, 24);		
}
