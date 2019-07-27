#include "bt.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* malloc */

#define CLEAR "\033[0m"
#define GREEN "\x1B[32m"
#define RED   "\x1B[31m"
#define CYAN  "\x1B[36m"

#define TEST_EQUAL(res, expected) \
++test_no; ++g_total_tests;\
printf("\ttest %lu: expected: %d, got: %d\n",\
test_no, expected, res); result *= (expected == res); \
(expected == res) ? (++g_total_success) : (++g_total_failed);

#define TEST_SUMMARY(tot, success, fail) \
printf(CYAN "\nTest Result Summary:\n" CLEAR); \
printf("Total:     %lu [100.0%%]\n", tot); \
printf(RED "Failed:     %lu [%.1f%%]\n" CLEAR, fail, \
((float)fail / tot) * 100); \
printf(GREEN "Succeeded: %lu [%.1f%%]\n" CLEAR, success, \
((float)success / tot) * 100);


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

size_t g_total_tests = 0;
size_t g_total_success = 0;
size_t g_total_failed = 0;

int Test_BTCreate();
int Test_BTInsert();

int main()
{
	RUN_TEST(Test_BTCreate);
	RUN_TEST(Test_BTInsert);

	return 0;
}

int Test_BTCreate()
{
	bt_t *bt = NULL;
	bt = BTCreate(32);
	BTDestroy(bt);
	return bt != NULL;
}

int Test_BTInsert()
{
	uint32_t x = 0;
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	bt_t *bt = NULL;
	bt = BTCreate(8);
	x = 8;
	BTInsert(bt, x);
	res = BTCount(bt);
	TEST_EQUAL(res, 1);




	BTDestroy(bt);
	return result;

}

