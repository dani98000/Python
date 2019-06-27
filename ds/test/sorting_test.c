#include "../include/sorting.h"

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


int IsBefore(const void *left, const void *right)
{
	return(*(int *)(left) - *(int *)(right));
}

int main()
{
	int arr[] = {8,5,9,1,5};
	int i = 0;
	
	
	puts("Before sort: ");
	for(; i < 5; i++)
	{
		printf("%d",arr[i]);
	}
	
	BubbleSort((int *)arr, 5, sizeof(int), IsBefore);
	
	puts("\nAfter sort: ");
	for(i = 0; i < 5; i++)
	{
		printf("%d",arr[i]);
	}
	
	return 0;
}
