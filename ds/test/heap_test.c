#include "heap.h" /* My header file */
#include "dvec.h"

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

static int cmp(const void *data1, const void *data2, const void *params);
static int ShouldRemove(const void *data, const void *key, const void *params);
static int IsSorted(heap_t *heap);

int Test_Push();
int Test_Pop();
int Test_Remove();
int Test_Remove2();
int Test_Debugging();

int main()
{
	RUN_TEST(Test_Push);
	RUN_TEST(Test_Pop);
	RUN_TEST(Test_Remove);
	RUN_TEST(Test_Remove2);
	RUN_TEST(Test_Debugging);


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
	int arr[] = {5, 20, 8, 16, 1, 10, 21, 31, 17, 3, 13};
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

int Test_Remove()
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

	HeapRemove(heap, ShouldRemove, &arr[1]); /*remove 20*/

	/*TEST3*/
	res = HeapSize(heap);
	TEST_EQUAL(res, arr_length - 1);


	/*IsSorted(heap);*/
	printf("\n");
	HeapDestroy(heap);

	return result;		
}

int Test_Remove2()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	int i = 0;
	int n = 0;
	int arr[] = {100, 36, 93, 2, 7, 90, 92};
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
	TEST_EQUAL(res, 100);

	HeapRemove(heap, ShouldRemove, &arr[4]); /*remove 7*/

	/*TEST3*/
	res = HeapSize(heap);
	TEST_EQUAL(res, arr_length - 1);

	/*TEST4*/
	res = IsSorted(heap);
	TEST_EQUAL(res, 1);

	HeapDestroy(heap);

	return result;		
}

static int cmp(const void *data1, const void *data2, const void *params)
{
	(void)params;

	return(*(int *)data1 < *(int *)data2);
}

static int ShouldRemove(const void *data, const void *key, const void *params)
{
	(void)(params);

	return(*(int *)data == *(int *)key);
}

static int IsSorted(heap_t *heap)
{
	int i = 0;
	int temp[100] = {0};
	int res = 1;
	heap_t *temp_heap = HeapCreate(cmp);
	int size = HeapSize(heap); 

	for(; i < size; ++i)
	{
		temp[i] = *(int *)HeapPeek(heap);
		HeapPop(heap);
		HeapPush(temp_heap, &temp[i]);	
	}
	for(i = 0; i < size; ++i)
	{
		if(temp[i+1] < temp[i])
		{
			res *= 1;
		}
		else
		{
			res = 0;
		}
	}
	for(i = 0; i < size; ++i)
	{
		temp[i] = *(int *)HeapPeek(temp_heap);
		HeapPop(temp_heap);
		HeapPush(heap, &temp[i]);	
	}
	return res;
}

typedef struct
{
    char *name;
    int serial;
}dog_t;

int CompareDogTags(const void *dog1, const void *dog2, const void *nothing)
{
    (void)nothing;    
    return ((dog_t *)dog2)->serial > ((dog_t* )dog1)->serial;
}

int Test_Debugging()
{
    int flag = 1;
    int evaluation = 0;
    int test_num = 0;
    dog_t dog1, dog2, tempdog;
    heap_t *heap = NULL;    heap = HeapCreate(CompareDogTags);

    if (NULL == heap)
    {
        return 0;
    }    

    dog1.name = "boshy";
    dog2.name = "kiril";
    dog1.serial = 2;
    dog2.serial = 2;    /* 1 */

    HeapPush(heap, &dog1);
    HeapPush(heap, &dog2);

    tempdog = *(dog_t* )HeapPeek(heap);    
    printf("%s\n", tempdog.name);    HeapPop(heap);

    HeapPush(heap, &tempdog);
    tempdog = *(dog_t* )HeapPeek(heap);    

    printf("%s\n", tempdog.name);    /* cleanup */

    HeapDestroy(heap);    (void)evaluation;
    (void)test_num;

    return flag;
}