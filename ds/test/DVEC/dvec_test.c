#include <stdio.h>
#include <stdlib.h>

#include "../../include/DVEC/dvec.h"

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
/*int Test_DvecSizeUp(void);*/


int main()
{
			
	RUN_TEST(Test_DvecPop);	
	RUN_TEST(Test_DvecPeek);	
	RUN_TEST(Test_DvecPush);
	/*RUN_TEST(Test_DvecSizeUp);*/
	
	
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
	/*int nums[3] = {0, 7, 9};*/
	int num = 1;
	int result = 1;
	int res = 0;
	dvec_t *dvec2 = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec2 = DVECCreate(sizeof(int), n_elements);
	
	DVECPushBack(dvec2, &num);
	num = 2;
	DVECPushBack(dvec2, &num);
	num = 3;
	DVECPushBack(dvec2, &num);

	/* test1 */
	res = *((int *)DVECGetItemAddress((void *)dvec2,0));
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	/* test2 */
	res = *(int *)DVECGetItemAddress(dvec2,1);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	
	/* test3 */
	res = *(int *)DVECGetItemAddress(dvec2,2);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	/* test4 */
	res = *(int *)DVECGetItemAddress(dvec2,3);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec2);

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
	dvec_t *dvec3 = NULL;
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

	dvec3 = DVECCreate(sizeof(int), n_elements);
	
	for(; i < n_elements-10; ++i)
	{
		DVECPushBack(dvec3, &nums[i]);
	}

	/* test1 */
	res = DVECSize(dvec3);
	expect = 90;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec3);
	free(nums);

	return result;
}

/*int test_resize()
{
	dvec_t *dvec = DVECCreate(sizeof(int),4); 
	int result = 1;
	int a=8,b =5,c=4,d=3 ,n=0;
	printf("capacity: %lu\n",(DVECCapacity(dvec)));
	printf("size : %lu\n",(DVECSize(dvec)));

	
	DVECPushBack(dvec,&a);
	printf("capacity: %lu\n",(DVECCapacity(dvec)));
	printf("size : %lu\n",(DVECSize(dvec)));
	n = *((int *)DVECGetItemAddress((void *)dvec,0));
	printf("%d\n",n);
	
	
	DVECPushBack(dvec,&b);
	printf("capacity: %lu\n",(DVECCapacity(dvec)));
	printf("size : %lu\n",(DVECSize(dvec)));
	n = *((int *)DVECGetItemAddress((void *)dvec,1));
	printf("%d\n",n);
	
	DVECPushBack(dvec,&c);
	printf("capacity: %lu\n",(DVECCapacity(dvec)));
	printf("size : %lu\n",(DVECSize(dvec)));	
	n = *((int *)DVECGetItemAddress((void *)dvec,2));
	printf("%d\n",n);
	
	DVECPushBack(dvec,&d);
	printf("capacity: %lu\n",(DVECCapacity(dvec)));
	printf("size : %lu\n",(DVECSize(dvec)));
	n = *((int *)DVECGetItemAddress((void *)dvec,3));
	printf("%d\n",n);
	

DVECPushBack(dvec,&d);
	printf("capacity: %lu\n",(DVECCapacity(dvec)));
	printf("size : %lu\n",(DVECSize(dvec)));
	n = *((int *)DVECGetItemAddress((void *)dvec,3));
	printf("%d\n",n);
	
	DVECPushBack(dvec,&d);
	printf("capacity: %lu\n",(DVECCapacity(dvec)));
	printf("size : %lu\n",(DVECSize(dvec)));
	n = *((int *)DVECGetItemAddress((void *)dvec,3));
	printf("%d\n",n);
	
	DVECPushBack(dvec,&d);
	printf("capacity: %lu\n",(DVECCapacity(dvec)));
	printf("size : %lu\n",(DVECSize(dvec)));
	n = *((int *)DVECGetItemAddress((void *)dvec,3));
	printf("%d\n",n);
	
	
	return result;
}

int test_size()
{
	stack_t *stack = STACKCreate(4, sizeof(int)); 
	int x = 4;
	int y = 5;
	int s = 6;
	int b = 8;
	int result = 1;
	
	STACKPush(stack, &y); 
	STACKPush(stack, &x); 
	STACKPush(stack, &s); 
	STACKPush(stack, &b); 
	
	result *= (STACKSize(stack) == 4);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 3);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 2);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 1);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 0);
	
	STACKPop((void *)stack);
	result *= (STACKSize(stack) == 0);
	
	STACKDestroy(stack);
	return result;
}*/
