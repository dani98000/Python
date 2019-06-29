#include <time.h>
#include <stdio.h>

#include "../include/sorting.h"

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

size_t g_total_tests = 0;
size_t g_total_success = 0;
size_t g_total_failed = 0;

int Test_BubbleSort();
int Test_InsertionSort();
int Test_SelectionSort();
int test();

int main()
{
	RUN_TEST(Test_BubbleSort);
	RUN_TEST(Test_InsertionSort);
	RUN_TEST(Test_SelectionSort);
	
	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	
	return 0;
}

int Test_BubbleSort()
{
	clock_t start_t, end_t, total_t;
    int my_array[5000];
	int i = 0;
	int result = 1;
	size_t test_no = 0;

	srand(0);
	
	for (; i < 5000; i++) 
	{
    	my_array[i] = rand() % 5000;
	}
	
	for(i = 0; i < 4999; i++)
	 {
        if(my_array[i] <= my_array[i+1])
        {
			result *=1;
		}
		else
		{
			result = 0;
		} 
 	 }
 	 TEST_EQUAL(result, 0);
 	 
 	 result = 1;
 	 start_t = clock();
 	 BubbleSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	 end_t = clock();
   
 	 
 	 for(i = 0; i < 4999; i++)
	 {
        if(my_array[i] <= my_array[i+1])
        {
			result *=1;
		}
		else
		{
			result = 0;
		} 
 	 }
 	 
     total_t = (double)(end_t - start_t);
     printf("Total clock ticks        :%lu\n", total_t);

 	 TEST_EQUAL(result, 1);
 	 
 	 return result;
}

int Test_InsertionSort()
{
	int my_array[5000];
	int i = 0;
	int result = 1;
	size_t test_no = 0;
	
	srand(0);
	
	for (; i < 5000; i++) 
	{
    	my_array[i] = rand() % 5000;
	}
	
	
	for(i = 0; i < 4999; i++)
	 {
        if(my_array[i] <= my_array[i+1])
        {
			result *=1;
		}
		else
		{
			result = 0;
		} 
 	 }
 	 TEST_EQUAL(result, 0);
 	 
 	 result = 1;
 	 InsertionSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	 
 	 for(i = 0; i < 4999; i++)
	 {
        if(my_array[i] <= my_array[i+1])
        {
			result *=1;
		}
		else
		{
			result = 0;
		} 
 	 }
 	 TEST_EQUAL(result, 1);
 	 
 	 return result;
}
int Test_SelectionSort()
{
	int my_array[5000];
	int i = 0;
	int result = 1;
	size_t test_no = 0;
	
	srand(0);
	
	for (; i < 5000; i++) 
	{
    	my_array[i] = rand() % 5000;
	}
	
	
	for(i = 0; i < 4999; i++)
	 {
        if(my_array[i] <= my_array[i+1])
        {
			result *=1;
		}
		else
		{
			result = 0;
		} 
 	 }
 	 TEST_EQUAL(result, 0);
 	 
 	 result = 1;
 	 SelectionSort((int *)my_array, 5000, sizeof(int), IsBefore);
 	 
 	 for(i = 0; i < 4999; i++)
	 {
        if(my_array[i] <= my_array[i+1])
        {
			result *=1;
		}
		else
		{
			result = 0;
		} 
 	 }
 	 TEST_EQUAL(result, 1);
 	 
 	 return result;
}
