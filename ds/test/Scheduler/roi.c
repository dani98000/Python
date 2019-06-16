/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 06/14/2019                              *
*   Description: Single Process Scheduler Tests   *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */
#include <time.h>   /* time   */
#include <unistd.h> /* access */

#include "tests.h" /* test macros */
#include "../../include/Scheduler/scheduler.h"

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

int Test_CreateDestroy(void);
int Test_AddRemove(void);
int Test_Run(void);

long TestFunc(void *params);
long StopExecution(void *scheduler);
long CoffeeBreak(void *check_interval);

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	RUN_TEST(Test_CreateDestroy);
	RUN_TEST(Test_AddRemove);
	RUN_TEST(Test_Run);

	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	

	return 0;
}

int Test_CreateDestroy(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	scd_t *scheduler = NULL;

	puts("\x1B[33m[Test_CreateDestroy]\033[0m");

	scheduler = ScdCreate();

	/* test1 */
	TEST_EQUAL(res, 0);
	
	ScdDestroy(scheduler);

	return result;
}

int Test_AddRemove(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	scd_t *scheduler = NULL;
	unid_t uid1, uid2;

	puts("\x1B[33m[Test_AddRemove]\033[0m");

	scheduler = ScdCreate();

	/* test1 */
	res = (int)ScdSize(scheduler);
	TEST_EQUAL(res, 0);
	
	/* test2 */
	res = ScdIsEmpty(scheduler);
	TEST_EQUAL(res, 1);
	
	uid1 = ScdAdd(scheduler, 4, TestFunc, NULL);
	
	/* test3 */
	res = UIDIsBad(uid1);
	TEST_EQUAL(res, 0);
	
	/* test4 */
	res = (int)ScdSize(scheduler);
	TEST_EQUAL(res, 1);
	
	/* test5 */
	res = ScdIsEmpty(scheduler);
	TEST_EQUAL(res, 0);
	
	uid2 = ScdAdd(scheduler, 40, StopExecution, scheduler);
	
	/* test6 */
	res = UIDIsBad(uid2);
	TEST_EQUAL(res, 0);
	
	/* test7 */
	res = (int)ScdSize(scheduler);
	TEST_EQUAL(res, 2);
	
	/* test8 */
	res = ScdIsEmpty(scheduler);
	TEST_EQUAL(res, 0);
	
	/* test9 */
	res = ScdRemove(scheduler, uid1);
	TEST_EQUAL(res, 0);
	
	/* test10 */
	res = (int)ScdSize(scheduler);
	TEST_EQUAL(res, 1);
	
	ScdDestroy(scheduler);

	return result;
}

int Test_Run(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	scd_t *scheduler = NULL;
	time_t now = time(NULL);
	int data = 1;
	unid_t uid1;

	puts("\x1B[33m[Test_Run]\033[0m");

	/* flow 1 */
	scheduler = ScdCreate();

	ScdAdd(scheduler, 1, CoffeeBreak, (void *)1);
	
	ScdAdd(scheduler, 1, TestFunc, &data);
	
	ScdAdd(scheduler, 10, StopExecution, scheduler);
	
	now = time(NULL);
	
	printf("\tstarted at: %s", ctime(&now));
	
	ScdRun(scheduler);
	
	printf("\tran for total of %ld sec\n", time(NULL) - now);
	/* test1 */
	res = (int)(time(NULL) - now);
	TEST_EQUAL(res, 10);
	printf("\n");
	
	ScdDestroy(scheduler);
	
	/* flow 2 */
	data = 0;
	
	scheduler = ScdCreate();

	ScdAdd(scheduler, 1, CoffeeBreak, (void *)1);
	
	uid1 = ScdAdd(scheduler, 1, TestFunc, &data);
	
	ScdAdd(scheduler, 10, StopExecution, scheduler);
	
	now = time(NULL);
	
	printf("\tstarted at: %s", ctime(&now));
	
	ScdRun(scheduler);
	
	printf("\tran for total of %ld sec\n", time(NULL) - now);
	
	/* test2 */
	res = (int)(time(NULL) - now);
	TEST_EQUAL(res, 21);
	printf("\n");
	
	now = time(NULL);
	printf("\tfinished at: %s", ctime(&now));
	
	sleep(1);
	
	/* test3 */
	res = ScdSize(scheduler);
	TEST_EQUAL(res, 2);
	
	/* flow 3 */
	data = 0;
	now = time(NULL);
	
	printf("\tstarted at: %s", ctime(&now));
	
	ScdAdd(scheduler, 10, StopExecution, scheduler);
	
	ScdRun(scheduler);
	
	printf("\tran for total of %ld sec\n", time(NULL) - now);
	/* test4 */
	res = (int)(time(NULL) - now);
	TEST_EQUAL(res, 21);
	printf("\n");
	
	now = time(NULL);
	printf("\tfinished at: %s", ctime(&now));
	
	/* flow 4 */
	data = 0;
	now = time(NULL);
	
	/* test5 */
	res = ScdRemove(scheduler, uid1);
	TEST_EQUAL(res, 0); 
	
	printf("\tstarted at: %s", ctime(&now));
	
	ScdAdd(scheduler, 10, StopExecution, scheduler);
	
	ScdRun(scheduler);
	
	printf("\tran for total of %ld sec\n", time(NULL) - now);
	/* test5 */
	res = (int)(time(NULL) - now);
	TEST_EQUAL(res, 10);
	printf("\n");
	
	now = time(NULL);
	printf("\tfinished at: %s", ctime(&now));
	
	
	ScdDestroy(scheduler);

	return result;
}

long TestFunc(void *params)
{
	time_t now = time(NULL);
	printf("\texecuted at: %s", ctime(&now));
	++(*(int *)params);
	
	if(5 == *(int *)params)
	{
		fopen("stop", "a");
	}
	
	return 0; /* dont change interval */
}

long StopExecution(void *scheduler)
{
	time_t now = time(NULL);
	printf("\tstopping at: %s", ctime(&now));
	
	ScdStop(scheduler);
	
	return -1; /* remove task */
}

long CoffeeBreak(void *check_interval)
{
	const char *filename = "stop";
	time_t now = time(NULL);
	int count = 4;
	
	if(-1 != access(filename, F_OK))
	{
		printf("\ttaking a coffee break: %s", ctime(&now));
		while(-1 != access(filename, F_OK))
		{
			sleep((int)(long)check_interval);
			if(0 >= count)
			{
				remove(filename);
			}
			--count;
		}
		printf("\ttook a break of: %ld sec\n", time(NULL) - now);
		now = time(NULL);
		printf("\treturning from coffee break: %s", ctime(&now));	
	}
	

	return 0;
}


































