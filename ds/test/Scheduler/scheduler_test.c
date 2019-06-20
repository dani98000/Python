#include <stdio.h>
#include <unistd.h>
#include <time.h>

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

unid_t Global_UID;

int IsExists(const char * filename)
{
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

long PeeBreak(void *params)
{
	int count = 5;
	char *file_name = "stop";
	FILE *file = fopen(file_name,"w");
	UNUSED(params);
	
	while(IsExists(file_name))
	{
		if(0 == count)
		{
			remove(file_name);
		}
		sleep(1);
		--count;
	}
	fclose(file);
	
	return -1;
}

long Func1(void *params)
{	
	UNUSED(params);
	

	
	return 2;			
}

long Func2(void *params)
{	
	UNUSED(params);
	

	
	return 10;			
}

long Func3(void *params)
{	
	*(int *)params = *(int *)params + 1;

	
	return 5;			
}

long RemoveFromFunc(void *params)
{
	ScdRemove(params , Global_UID);
	
	return -1;
}

long AddFromFunc(void *params)
{
	ScdAdd(params, 2, Func1, NULL);
	
	return -1;
}

long stop(void *params)
{	
	ScdStop(params);

	
	return -1;			
}

int Test_ScdSize();
int Test_ScdRemove();
int Test_File();
int Test_Flow();
int Test_RemoveFromFunc();
int Test_AddFromFunc();

int main(void)
{
	RUN_TEST(Test_ScdSize);
	RUN_TEST(Test_ScdRemove);
	RUN_TEST(Test_File);	
	RUN_TEST(Test_Flow);
	RUN_TEST(Test_RemoveFromFunc);	
	RUN_TEST(Test_AddFromFunc);	
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

int Test_File()
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	time_t before_run = time(NULL);
	time_t after_run;	
	scd_t * scd = ScdCreate();
	/*unid_t uid = bad_uid;
	unid_t uid2 = bad_uid;*/
	/*ScdAdd(scd, 2, Func1, NULL);*/
	/*ScdAdd(scd, 3, Func2, NULL);*/
	/*ScdAdd(scd, 3, stop, scd);*/
	ScdAdd(scd, 3, PeeBreak, NULL);
	ScdRun(scd);
	after_run = time(NULL);
	
	/* Test1 */
	res = after_run - before_run;
	TEST_EQUAL(res, 9);	


	ScdDestroy(scd);
		
	return result;
}

int Test_Flow()
{
	int result = 1;
	int a = 0;
	size_t test_no = 0;
	int res = 0;
	scd_t * scd = ScdCreate();
	time_t before_run = time(NULL);
	time_t after_run;	
	time(&before_run);
	time(&after_run);

	ScdAdd(scd, 2, Func1, NULL);
	ScdAdd(scd, 2, stop, scd);
	ScdAdd(scd, 3, Func3, &a);
	ScdRun(scd);
	after_run = time(NULL);
	printf("-----------------------------------------------------\n");
	printf("Beggining      :  %s", ctime(&before_run));
	printf("After first run:  %s\n", ctime(&after_run));
	/* Test1 */
	res = after_run - before_run;
	TEST_EQUAL(res,2);	
	printf("-----------------------------------------------------\n");
	
	ScdAdd(scd, 10, stop, scd);
	ScdRun(scd);
	after_run = time(NULL);
	printf("After second run:  %s\n", ctime(&after_run));
	/* Test2 */
	res = a;
	TEST_EQUAL(res,2);	
	printf("-----------------------------------------------------\n");
	
	ScdDestroy(scd);
	
	scd = ScdCreate();
	before_run = time(NULL);
	
	ScdAdd(scd, 2, Func1, NULL);
	ScdAdd(scd, 10, stop, scd);
	ScdAdd(scd, 3, Func3, &a);
	ScdRun(scd);
	after_run = time(NULL);
	printf("After third run:  %s\n", ctime(&after_run));
	/* Test2 */
	res = a;
	TEST_EQUAL(res, 4);	
	printf("-----------------------------------------------------\n");
	
	ScdDestroy(scd);
	
		
	return result;
}

int Test_RemoveFromFunc()
{
	int result = 1;
	int a = 0;
	size_t test_no = 0;
	int res = 0;
	scd_t * scd = ScdCreate();
	unid_t uid = bad_uid;
	unid_t uid2 = bad_uid;
	
	Global_UID = ScdAdd(scd, 2, Func1, NULL);
	ScdAdd(scd, 2, RemoveFromFunc, scd);
	
	res = ScdSize(scd);
	TEST_EQUAL(res, 2);	
	
	ScdRun(scd);
	
	res = ScdSize(scd);
	TEST_EQUAL(res, 0);
	
	ScdDestroy(scd);
		
	return result;
}

int Test_AddFromFunc()
{
	int result = 1;
	int a = 0;
	size_t test_no = 0;
	int res = 0;
	scd_t * scd = ScdCreate();
	unid_t uid = bad_uid;
	unid_t uid2 = bad_uid;
	
	ScdAdd(scd, 2, AddFromFunc, scd);
	ScdAdd(scd, 3, stop, scd);
	
	res = ScdSize(scd);
	TEST_EQUAL(res, 2);	
	
	ScdRun(scd);
	
	res = ScdSize(scd);
	TEST_EQUAL(res, 1);
	
	ScdDestroy(scd);
		
	return result;
}
