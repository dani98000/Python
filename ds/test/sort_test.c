#include <time.h>
#include <stdio.h>

#include "../include/sort.h"

#define UNUSED(x) (void)(x)

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

int IsBefore(const void *left, const void *right)
{
	return(*(int *)(left) - *(int *)(right));
}

size_t char_ktn(const void *value, const void *args)
{
	size_t res = 0;
	UNUSED(args);
	res = (size_t)*(char *)value - 97;
	return res;
}

size_t ktn(const void *value, const void *args)
{
	size_t res = 0;
	UNUSED(args);
	res = *(int *)value;
	return res;
}

size_t g_total_tests = 0;
size_t g_total_success = 0;
size_t g_total_failed = 0;

static int IsSorted(int *arr);
static void ArrayInit(int *arr);
int Test_BubbleSort();
int Test_InsertionSort();
int Test_SelectionSort();
int Test_CountingSort();
int Test_RadixSort();

int main()
{
	RUN_TEST(Test_BubbleSort);
	RUN_TEST(Test_InsertionSort);
	RUN_TEST(Test_SelectionSort);
	RUN_TEST(Test_CountingSort);	
	/*RUN_TEST(Test_RadixSort);*/
	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	
	return 0;
}

int Test_BubbleSort()
{
	clock_t start_t, end_t;
	double seconds = 0.0;
	double total_time = 0.0;
    int my_array[5000];
	int result = 1;
	int res = 0;
	size_t test_no = 0;


	/* test1*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	BubbleSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%.3f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test2*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	BubbleSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test3*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	BubbleSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);	
 	
 	printf("\tOn Average it takes "CYAN"[%f ms]"CLEAR" to BubbleSort an array of 5000 integers.\n", (total_time * 1000/ 3));
 	 
	return result;   
}

int Test_InsertionSort()
{	
	clock_t start_t, end_t;
	double seconds = 0.0;
	double total_time = 0.0;
    int my_array[5000];
	int result = 1;
	int res = 0;
	size_t test_no = 0;


	/* test1*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	InsertionSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test2*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	InsertionSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test3*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	InsertionSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);	
 	
 	printf("\tOn Average it takes "CYAN"[%f ms]"CLEAR" to InsertionSort an array of 5000 integers.\n", (total_time * 1000/ 3));
 	 	 
	return result;
}
int Test_SelectionSort()
{
	clock_t start_t, end_t;
	double seconds = 0.0;
	double total_time = 0.0;
    int my_array[5000];
	int result = 1;
	int res = 0;
	size_t test_no = 0;


	/* test1*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	SelectionSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test2*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	SelectionSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test3*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	SelectionSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);	
 	
 	printf("\tOn Average it takes "CYAN"[%f ms]"CLEAR" to SelectionSort an array of 5000 integers.\n", (total_time * 1000/ 3));
 	 
	return result;
}

int Test_CountingSort()
{
	clock_t start_t, end_t;
	double seconds = 0.0;
	double total_time = 0.0;
    int my_array[5000];
	int result = 1;
	int res = 0;
	size_t test_no = 0;


	/* test1*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	CountingSort(my_array, 5000, 4, ktn, NULL, 5000);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test2*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	CountingSort(my_array, 5000, 4, ktn, NULL, 5000);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test3*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	CountingSort(my_array, 5000, 4, ktn, NULL, 5000);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);	
 	
 	printf("\tOn Average it takes "CYAN"[%f ms]"CLEAR" to CountingSort an array of 5000 integers.\n", (total_time * 1000/ 3));
 	 
	return result;
}

int Test_RadixSort()
{
	clock_t start_t, end_t;
	double seconds = 0.0;
	double total_time = 0.0;
    int my_array[5000];
	int result = 1;
	int res = 0;
	size_t test_no = 0;


	/* test1*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	RadixSort(my_array, 5000, sizeof(int), ktn, NULL, 4);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test2*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	RadixSort(my_array, 5000, sizeof(int), ktn, NULL, 4);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);
 	
	/* test3*/
	ArrayInit(my_array);
	
 	start_t = clock();	
	RadixSort(my_array, 5000, sizeof(int), ktn, NULL, 4);
 	end_t = clock();
 	
	seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	total_time += seconds;
	printf( "\tsorted in " CYAN"[%f ms]\n" CLEAR, seconds * 1000);
	
	res = IsSorted(my_array);	
 	TEST_EQUAL(res, 1);	
 	
 	printf("\tOn Average it takes "CYAN"[%f ms]"CLEAR" to RadixSort an array of 5000 integers.\n", (total_time * 1000/ 3));
 	 
	return result;
}


void ArrayInit(int *arr)
{
	int i = 0;
	
	for(; i < 5000; i++) 
	{
    	arr[i] = rand() % 5000;
	}
}

int IsSorted(int *arr)
{
	int result = 1;
	int i = 0; 
	
	for(; i < 4999; i++)
	{
		if(arr[i] <= arr[i+1])
        {
			result *=1;
		}
		else
		{
			result = 0;
		} 
 	 }
 	 
 	 return result;
}


