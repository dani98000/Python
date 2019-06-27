#include <stdio.h>
#include <stdlib.h>

#include "../include/dvec.h"

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

int Test_DvecPeek(void);
int Test_DvecPop(void);
int Test_DvecPush(void);
int Test_DvecSizeUp(void);
int Test_DvecSizeDown(void);
int Test_DvecReserve(void);

/*void test_create()
{
	dvec_t *dvec = NULL;
	size_t expected = 5;
	char *field = NULL;
	
	dvec = DVECCreate(5, 5);
	
	DVECDestroy(dvec);
}*/

int main()
{	
	RUN_TEST(Test_DvecPop);	
	RUN_TEST(Test_DvecPeek);
	RUN_TEST(Test_DvecPush);
	RUN_TEST(Test_DvecSizeDown);
	RUN_TEST(Test_DvecSizeUp);
	RUN_TEST(Test_DvecReserve);	
	
	return 0;
}

int Test_DvecPop(void)
{
	int num = 3;
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec = DVECCreate(sizeof(num), n_elements);

	DVECPushBack(dvec,&num);
	num = 4;
	DVECPushBack(dvec,&num);
	num = 9;
	DVECPushBack(dvec,&num);

	/* test1 */
	res = DVECSize(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPopBack(dvec);

	/* test2 */
	res = DVECSize(dvec);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPopBack(dvec);
	
	/* test3 */
	res = DVECSize(dvec);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPopBack(dvec);

	/* test4 */
	res = DVECSize(dvec);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);

	DVECPopBack(dvec);
	result *= (expect == res);

	/* test6 */
	res = DVECSize(dvec);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPopBack(dvec);

	/* test7 */
	res = DVECSize(dvec);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	DVECDestroy(dvec);

	return result;
}

int Test_DvecPeek()
{
	int num = 1;
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec = DVECCreate(sizeof(num), n_elements);
	
	DVECPushBack(dvec, &num);
	num = 2;
	DVECPushBack(dvec, &num);
	num = 3;
	DVECPushBack(dvec, &num);

	/* test1 */
	res = *((int *)DVECGetItemAddress(dvec,0));
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	/* test2 */
	res = *(int *)DVECGetItemAddress(dvec,1);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	
	/* test3 */
	res = *(int *)DVECGetItemAddress(dvec,2);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	/* test4 */
	res = *(int *)DVECGetItemAddress(dvec,3);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_DvecPush(void)
{
	size_t n_elements = 100;
	int *nums;
	int j = 0;
	size_t i = 0;
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;

	nums = (int *)malloc(n_elements * sizeof(int));
	if(NULL == nums)
	{
		perror("malloc error!");
		return 1;
	}

	/* fill array for testing */
	for(; i < n_elements; ++i)
	{
		nums[i] = ++j;
	}

	i = 0;

	dvec = DVECCreate(sizeof(int), n_elements);
	
	for(; i < n_elements-10; ++i)
	{
		DVECPushBack(dvec, &nums[i]);
	}

	/* test1 */
	res = DVECSize(dvec);
	expect = 90;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);
	free(nums);

	return result;
}

int Test_DvecSizeUp(void)
{
	int num = 1;
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 4;

	dvec = DVECCreate(sizeof(int), n_elements);
	
	DVECPushBack(dvec, &num);
	num = 2;
	DVECPushBack(dvec, &num);
	num = 3;
	DVECPushBack(dvec, &num);
	
	res = DVECCapacity(dvec);
	expect = 4;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DVECPushBack(dvec, &num);	

	res = DVECCapacity(dvec);
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DVECDestroy(dvec);
	
	return result;
}

int Test_DvecSizeDown(void)
{
	int num = 1;
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 4;

	dvec = DVECCreate(sizeof(int), n_elements);
	
	DVECPushBack(dvec, &num);
	num = 2;
	DVECPushBack(dvec, &num);
	num = 3;
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);	

	res = DVECCapacity(dvec);
	expect = 8;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DVECPopBack(dvec);
	DVECPopBack(dvec);
		
	res = DVECCapacity(dvec);
	expect = 4;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DVECDestroy(dvec);
	
	return result;
}

int Test_DvecReserve(void)
{
	int num = 1;
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 10;

	dvec = DVECCreate(sizeof(int), n_elements);
	
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);	
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);	

	DVECReserve(dvec, 10);
	res = DVECCapacity(dvec);
	expect = 10;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
		
	DVECPushBack(dvec, &num);		
		
	DVECReserve(dvec, 10);		
	res = DVECCapacity(dvec);
	expect = 11;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);
	
	DVECDestroy(dvec);
	
	return result;
}
