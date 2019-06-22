#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vsma.h"

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
	vsma_t *vsma = (vsma_t *)malloc(500 * sizeof(char));
	vsma_t *temp = NULL; 
	vsma = VSMAInit(vsma, 500);
	
	printf("%ld\n", *(size_t *)vsma);
	printf("magic number: %x\n", *(size_t *)((char *)vsma + 8) );
		printf("size: %ld\n",VSMACount(vsma));
		printf("larget free before alloc: %ld\n",VSMAFindLargestFree(vsma));
	temp = VSMAAlloc(vsma, 100);
			printf("larget free after alloc: %ld\n",VSMAFindLargestFree(vsma));
	printf("size: %ld\n",VSMACount(vsma));
	printf("%ld\n", *(long *)vsma);
	printf("%ld\n", *(long *)((char *)temp + 104));
	printf("%ld\n", *(long *)((char *)vsma + 468));
	VSMAFree(temp);
	printf("larget free after free: %ld\n",VSMAFindLargestFree(vsma));	
	printf("after free:%ld\n", *(long *)vsma);
	printf("size after free: %ld",VSMACount(vsma));
	
}

int Test_VSMAInit();
int Test_VSMAAlloc();
int Test_VSMACount();
int Test_VSMAFindLargestFree();

int main()
{
	/*test();*/
	RUN_TEST(Test_VSMAInit);
	RUN_TEST(Test_VSMAAlloc);
	RUN_TEST(Test_VSMACount);
	RUN_TEST(Test_VSMAFindLargestFree);	
	
	return 0;
}

int Test_VSMAInit()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	vsma_t *vsma = (vsma_t *)malloc(500 * sizeof(char));
	memset(vsma,5,464);
	vsma = VSMAInit(vsma, 500);
		
	/* test 1 */
	res = *(size_t *)((char *)vsma);
	TEST_EQUAL(res, 464);
		
	/* test 2 */
	res = *(size_t *)((char *)vsma + 464);
	TEST_EQUAL(res, 0);	
	
	return result;
}

int Test_VSMAAlloc()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	vsma_t *vsma = (vsma_t *)malloc(500 * sizeof(char));
	vsma_t *temp = NULL; 
	memset(vsma, 5, 464);
	vsma = VSMAInit(vsma, 500);

	temp = VSMAAlloc(vsma, 199);	
	
	/* test 1 */
	res = *(size_t *)((char *)temp - 16);
	TEST_EQUAL(res, -200);
	
	/* test 2 */	
	res = *(size_t *)((char *)temp + 200);
	TEST_EQUAL(res, 248);
	
	/* test 3 */	
	res = *(size_t *)((char *)vsma + 216);
	TEST_EQUAL(res, 248);
	
	/* test 4 */
	res = *(size_t *)((char *)vsma );
	TEST_EQUAL(res, -200);
	
	temp = VSMAAlloc(vsma, 100);	
	
	/* test 5 */
	res = *(size_t *)((char *)temp - 16);
	TEST_EQUAL(res, -104);
	
	/* test 6 */
	res = *(size_t *)((char *)vsma);
	TEST_EQUAL(res, -200);
	
	/* test 7 */
	res = *(size_t *)((char *)temp + 104);
	TEST_EQUAL(res, 128);	
	
	/* test 8 */
	res = *(size_t *)((char *)vsma + 336);
	TEST_EQUAL(res, 128);
	
	return result;
}

int Test_VSMACount()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	vsma_t *vsma = (vsma_t *)malloc(500 * sizeof(char));
	vsma_t *alloc1 = NULL;
	vsma_t *alloc2 = NULL;	 
	memset(vsma, 5, 464);
	vsma = VSMAInit(vsma, 500);	
	
	/* test 1 */
	res = VSMACount(vsma);
	TEST_EQUAL(res, 464);
	
	alloc1 = VSMAAlloc(vsma, 199);
	
	/* test 2 */
	res = VSMACount(vsma);
	TEST_EQUAL(res, 248);
	
	alloc2 = VSMAAlloc(vsma, 100);
	
	/* test 3 */
	res = VSMACount(vsma);
	TEST_EQUAL(res, 128);
	
	VSMAFree(alloc1);
	
	/* test 4 */
	res = VSMACount(vsma);
	TEST_EQUAL(res, 328);
	
	VSMAFree(alloc2);
	
	/* test 5 */
	res = VSMACount(vsma);
	TEST_EQUAL(res, 464);
	
	return result;	
}

int Test_VSMAFindLargestFree()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	vsma_t *vsma = (vsma_t *)malloc(500 * sizeof(char));
	vsma_t *alloc1 = NULL;
	vsma_t *alloc2 = NULL;
	memset(vsma, 5, 464);		 
	vsma = VSMAInit(vsma, 500);	
	
	/* test 1 */
	res = VSMACount(vsma);
	TEST_EQUAL(res, 464);
	
	alloc1 = VSMAAlloc(vsma, 199);
	
	/* test 2 */
	res = VSMACount(vsma);
	TEST_EQUAL(res, 248);
	
	alloc2 = VSMAAlloc(vsma, 100);
	
	/* test 3 */
	res = VSMACount(vsma);
	TEST_EQUAL(res, 128);

	VSMAFree(alloc2);
	
	/* test 4 */
	res = VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 248);
	
	alloc2 = VSMAAlloc(vsma, 100);	
	VSMAFree(alloc1);
	
	/* test 5 */
	res = VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 200);

	VSMAFree(alloc2);
	
	/* test 6 */
	res = VSMAFindLargestFree(vsma);
	TEST_EQUAL(res, 464);
	
	return result;	
}
