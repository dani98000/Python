#include "heap.h" /* My header file */

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

static int cmp(const void *data1, const void *data2);
int Test_Push();
int Test_Pop();

int main()
{
	/*heap_t *heap = HeapCreate(cmp);
	int a = 5;
	int b = 10;
	int c = 8;
	int n = 0;

	HeapPush(heap, &a);
	n = *(int *)HeapPeek(heap); 
	printf("%d\n", n);

	HeapPush(heap, &b);
	n = *(int *)HeapPeek(heap); 
	printf("%d\n", n);	

	HeapPush(heap, &c);
	n = *(int *)HeapPeek(heap); 
	printf("%d\n", n);

	HeapPop(heap);

	n = *(int *)HeapPeek(heap); 
	printf("%d\n", n);*/

	RUN_TEST(Test_Push);
	RUN_TEST(Test_Pop);






	/*TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);*/
	
	return 0;
}

int Test_Push()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	int i = 0;
	int n = 0;
	int arr[] = {5, 20, 8, 16, 1, 10, 21, 31, 17, 20, 13};
	int arr_length = sizeof(arr) / sizeof(int);
	
	heap_t *heap = HeapCreate(cmp);

	for(; i < arr_length; ++i)
	{
		HeapPush(heap, &arr[i]);
	}

	/*TEST1*/
	res = HeapSize(heap);
	TEST_EQUAL(res, arr_length);

	res = *(int *)HeapPeek(heap); 
	TEST_EQUAL(res, 31);

	HeapDestroy(heap);

	return result;		

}

int Test_Pop()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	int i = 0;
	int n = 0;
	int arr[] = {5, 20, 8, 16, 1, 10, 21, 31, 17, 20, 13};
	int arr_length = sizeof(arr) / sizeof(int);
	
	heap_t *heap = HeapCreate(cmp);

	for(; i < arr_length; ++i)
	{
		HeapPush(heap, &arr[i]);
	}

	/*TEST1*/
	res = HeapSize(heap);
	TEST_EQUAL(res, arr_length);

	/*TEST2*/
	res = *(int *)HeapPeek(heap); 
	TEST_EQUAL(res, 31);

	HeapPop(heap);
	
	/*TEST3*/
	res = HeapSize(heap);
	TEST_EQUAL(res, arr_length - 1);

	/*TEST4*/
	res = *(int *)HeapPeek(heap);
	TEST_EQUAL(res, 21);

	HeapDestroy(heap);

	return result;		
}

static int cmp(const void *data1, const void *data2)
{
	return(*(int *)data1 - *(int *)data2);
}

