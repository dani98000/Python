/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 28/05/19                                *
*   Description: Stack data structure implem.     *
*                                                 *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand   */

#include "../include/stack.h"

#define RUN_TEST(test) \
if(test()){ printf("\x1B[32m%-24s| %5s\n\033[0m", "["#test"]","OK!"); } \
else{ printf("\x1B[31m%-24s| %7s\n\033[0m", "["#test"]", "FAIL!"); }

#define SUCCESS (0)
#define FAILURE (1)

int Test_Int_StackSize(void);
int Test_Int_StackOverflow(void);
int Test_Int_StackPop(void);
int Test_Int_StackPeek(void);
int Test_Int_StackPush(void);

int Test_Struct_StackSize(void);
int Test_Struct_StackOverflow(void);
int Test_Struct_StackPop(void);
int Test_Struct_StackPeek(void);
int Test_Struct_StackPush(void);

typedef struct Doggie
{
	int id;
	char *name;
	int age;
	int gender;	
	int color;
	char *breed;
	enum fur_types
	{
		FURRY,
		VERRY_FURRY,
		FURRIEST,
		AMAZING
	} fur_type;
} doggie_t; 

int main() 
{
	puts("\x1B[36mTest Results:\033[0m");
	puts("\x1B[33m--- Basic Type Test Results: ---\033[0m");
	RUN_TEST(Test_Int_StackSize);
	RUN_TEST(Test_Int_StackOverflow);
	RUN_TEST(Test_Int_StackPop);
	RUN_TEST(Test_Int_StackPeek);
	RUN_TEST(Test_Int_StackPush);
	puts("\x1B[33m--- Doggie Type Test Results: ---\033[0m");
	RUN_TEST(Test_Struct_StackSize);
	RUN_TEST(Test_Struct_StackOverflow);
	RUN_TEST(Test_Struct_StackPop);
	RUN_TEST(Test_Struct_StackPeek);
	RUN_TEST(Test_Struct_StackPush);
	
	return 0;
}

int Test_Int_StackSize(void)
{
	int num = 3;
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	stk = STACKCreate(n_elements, sizeof(num));

	/* test1 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPush(stk, &num);
	num = 4;
	STACKPush(stk, &num);

	/* test2 */
	res = STACKSize(stk);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);
	
	/* test3 */
	res = STACKSize(stk);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKDestroy(stk);

	return result;
}

int Test_Int_StackOverflow(void)
{
	int num = 3;
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 1;

	stk = STACKCreate(n_elements, sizeof(num));

	/* test1 */
	res = STACKPush(stk, &num);
	expect = SUCCESS;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test2 */
	res = STACKPush(stk, &num);
	expect = FAILURE;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test2 */
	res = STACKPush(stk, &num);
	expect = SUCCESS;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKDestroy(stk);

	return result;
}

int Test_Int_StackPop(void)
{
	int num = 3;
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	stk = STACKCreate(n_elements, sizeof(num));

	STACKPush(stk, &num);
	num = 4;
	STACKPush(stk, &num);
	num = 9;
	STACKPush(stk, &num);

	/* test1 */
	res = STACKSize(stk);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test2 */
	res = STACKSize(stk);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);
	
	/* test3 */
	res = STACKSize(stk);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test4 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test6 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test7 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	STACKDestroy(stk);

	return result;
}

int Test_Int_StackPeek(void)
{
	int nums[3] = {0, 7, 9};
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	stk = STACKCreate(n_elements, sizeof(int));
	
	STACKPush(stk, &nums[0]);
	STACKPush(stk, &nums[1]);
	STACKPush(stk, &nums[2]);

	/* test1 */
	res = *(int *)STACKPeek(stk);
	expect = 9;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test2 */
	res = *(int *)STACKPeek(stk);
	expect = 7;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);
	
	/* test3 */
	res = *(int *)STACKPeek(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test4 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKDestroy(stk);

	return result;
}

int Test_Int_StackPush(void)
{
	size_t n_elements = 100;
	int *nums;
	size_t i = 0;
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
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
		nums[i] = rand() % n_elements;
	}

	i = 0;

	stk = STACKCreate(n_elements, sizeof(int));
	
	for(; i < n_elements; ++i)
	{
		STACKPush(stk, &nums[i]);
	}

	/* test1 */
	res = STACKSize(stk);
	expect = 100;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKDestroy(stk);
	free(nums);

	return result;
}

int Test_Struct_StackSize(void)
{
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;
	doggie_t dog1, dog2, dog3;

	stk = STACKCreate(n_elements, sizeof(doggie_t));

	/* test1 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPush(stk, &dog1);
	STACKPush(stk, &dog2);
	STACKPush(stk, &dog3);

	/* test2 */
	res = STACKSize(stk);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);
	STACKPop(stk);
	
	/* test3 */
	res = STACKSize(stk);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKDestroy(stk);

	return result;
}

int Test_Struct_StackOverflow(void)
{
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 1;
	doggie_t dog1, dog2;

	stk = STACKCreate(n_elements, sizeof(doggie_t));

	/* test1 */
	res = STACKPush(stk, &dog1);
	expect = SUCCESS;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test2 */
	res = STACKPush(stk, &dog2);
	expect = FAILURE;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test2 */
	res = STACKPush(stk, &dog2);
	expect = SUCCESS;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKDestroy(stk);

	return result;
}

int Test_Struct_StackPop(void)
{
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;
	doggie_t dog1, dog2, dog3;

	stk = STACKCreate(n_elements, sizeof(doggie_t));

	STACKPush(stk, &dog1);
	STACKPush(stk, &dog2);
	STACKPush(stk, &dog3);

	/* test1 */
	res = STACKSize(stk);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test2 */
	res = STACKSize(stk);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);
	
	/* test3 */
	res = STACKSize(stk);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test4 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test6 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test7 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	STACKDestroy(stk);

	return result;
}

int Test_Struct_StackPeek(void)
{
	doggie_t dogs[3] = {{1, NULL, 0, 0, 0, NULL, 0}, 
						{5, NULL, 0, 0, 0, NULL, 0},
						{12, NULL, 0, 0, 0, NULL, 0}};
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	stk = STACKCreate(n_elements, sizeof(int));
	
	STACKPush(stk, &dogs[0]);
	STACKPush(stk, &dogs[1]);
	STACKPush(stk, &dogs[2]);

	/* test1 */
	res = ((doggie_t *)STACKPeek(stk))->id;
	expect = 12;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test2 */
	res = ((doggie_t *)STACKPeek(stk))->id;
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);
	
	/* test3 */
	res = ((doggie_t *)STACKPeek(stk))->id;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKPop(stk);

	/* test4 */
	res = STACKSize(stk);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKDestroy(stk);

	return result;
}

int Test_Struct_StackPush(void)
{
	size_t n_elements = 100;
	doggie_t *dogs;
	size_t i = 0;
	int result = 1;
	int res = 0;
	stack_t *stk = NULL;
	int expect = 0;
	size_t test_no = 0;

	dogs = (doggie_t *)malloc(n_elements * sizeof(doggie_t));
	if(NULL == dogs)
	{
		perror("malloc error!");
		return 1;
	}

	i = 0;

	stk = STACKCreate(n_elements, sizeof(doggie_t));
	
	for(; i < n_elements; ++i)
	{
		STACKPush(stk, &dogs[i]);
	}

	/* test1 */
	res = STACKSize(stk);
	expect = 100;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	STACKDestroy(stk);
	free(dogs);

	return result;
}



