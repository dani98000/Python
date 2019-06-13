/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 13/06/19                                *
*   Description: Task Library Tests               *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <unistd.h> /* sleep */

#include "tests.h" /* test macros */
#include "../../include/Scheduler/task.h"

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

long TestFunc(void *params);

int Test_CreateDestroy(void);
int Test_GetTime(void);
int Test_GetUID(void);
int Test_Execute(void);

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	RUN_TEST(Test_CreateDestroy);
	RUN_TEST(Test_GetTime);
	RUN_TEST(Test_GetUID);
	RUN_TEST(Test_Execute);

	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	

	return 0;
}

long TestFunc(void *params)
{
	printf("\tcalled with param: %d\n", *(int *)params);
	return (long)*(int *)params;
}

int Test_CreateDestroy(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	task_t *t = NULL;	
	int param = 10;

	puts("\x1B[33m[Test_CreateDestroy]\033[0m");

	t = TaskCreate(100, TestFunc, &param);

	/* task1 */
	TEST_EQUAL(res, 0);
	
	TaskDestroy(t);

	return result;
}

int Test_GetTime(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	task_t *t = NULL;
	int param = 10;

	puts("\x1B[33m[Test_GetTime]\033[0m");

	t = TaskCreate(100, TestFunc, &param);

	/* task1 */
	res = TaskGetTime(t);
	TEST_NOT_EQUAL(res, 0);
	
	
	/* task2 */
	res = (int)time(NULL) + 100;
	TEST_EQUAL(((int)TaskGetTime(t)), res);
	
	TaskDestroy(t);

	return result;
}

int Test_GetUID(void)
{
	int result = 1;
	size_t test_no = 0;
	task_t *t = NULL;
	int param = 10;
	unid_t uid;

	puts("\x1B[33m[Test_GetTime]\033[0m");

	t = TaskCreate(100, TestFunc, &param);

	/* task1 */
	uid = TaskGetUID(t);
	TEST_EQUAL(((int)uid.counter), 3);
	
	/* task2 */
	uid = TaskGetUID(t);
	TEST_EQUAL(((int)uid.time.tv_sec), ((int)time(NULL)));
	
	TaskDestroy(t);

	return result;
}

int Test_Execute(void)
{
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	task_t *t = NULL;
	int param = 10;

	puts("\x1B[33m[Test_Execute]\033[0m");

	t = TaskCreate(100, TestFunc, &param);

	/* task1 */
	res = TaskGetTime(t);
	TEST_EQUAL(res, ((int)time(NULL) + 100));

	/* task2 */
	res = TaskExecute(t);
	TEST_EQUAL(res, 1);
	
	/* task3 */
	res = TaskGetTime(t);
	TEST_EQUAL(res, ((int)time(NULL) + param));
	
	param = -1;
	
	/* task4 */
	res = TaskExecute(t);
	TEST_EQUAL(res, 1);
	
	/* task5 */
	res = TaskGetTime(t);
	TEST_EQUAL(res, ((int)time(NULL) + 10));
	
	param = 0;
	
	/* task6 */
	res = TaskExecute(t);
	TEST_EQUAL(res, 0);
	
	param = -1;
	
	/* task7 */
	res = TaskExecute(t);
	TEST_EQUAL(res, 1);
	
	/* task8 */
	res = TaskGetTime(t);
	TEST_EQUAL(res, ((int)time(NULL) + 10));
	
	TaskDestroy(t);
	
	t = TaskCreate(0, TestFunc, &param);
	sleep(2);
	
	param = 10;
	
	/* task9 */
	res = TaskExecute(t);
	TEST_EQUAL(res, 1);
	
	/* task10 */
	res = TaskGetTime(t);
	TEST_EQUAL(res, ((int)time(NULL)));
	
	TaskDestroy(t);
	
	return result;
}


