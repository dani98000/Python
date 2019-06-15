#include <stdio.h>
#include "../../include/Scheduler/scheduler.h"

#define UNUSED(x) (void)(x)

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

long Func1(void *params)
/* Should run 2 times */
{	
	UNUSED(params);
	
	printf("Task 1 completed\n");
	
	return 0;			
}

long stop(void *params)
/* Should run 2 times */
{	
	ScdStop(params);
	printf("Task 2 completed\n");
	
	return -1;			
}

int Test_ScdSize();
int Test_ScdRemove();

int main(void)
{
	RUN_TEST(Test_ScdSize);
	RUN_TEST(Test_ScdRemove);	
}

int Test_ScdSize()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	scd_t * scd = ScdCreate();
	ScdAdd(scd, 2, Func1, NULL);
	ScdAdd(scd, 2, stop, scd);
	ScdRun(scd);
	ScdAdd(scd, 5, stop, scd);
	ScdRun(scd);
	
	res = ScdSize(scd);
	TEST_EQUAL(res,1);	
	
	ScdDestroy(scd);
		
	return result;
}

int Test_ScdRemove()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	scd_t * scd = ScdCreate();
	unid_t uid = bad_uid;
	unid_t uid2 = bad_uid;
	uid = ScdAdd(scd, 2, Func1, NULL);
	uid2 = ScdAdd(scd, 2, Func1, NULL);
	ScdAdd(scd, 3, stop, scd);
	ScdRun(scd);
	
	res = ScdSize(scd);
	TEST_EQUAL(res,2);
	
	ScdRemove(scd, uid);
	
	res = ScdSize(scd);
	TEST_EQUAL(res,1);	
	
	
	res = ScdIsEmpty(scd);
	TEST_EQUAL(res,0);	
	
	ScdRemove(scd, uid2);
	
	res = ScdIsEmpty(scd);
	TEST_EQUAL(res,1);
		
	ScdDestroy(scd);
		
	return result;
}
