#include <stdio.h>
#include <stdlib.h>

#include "vsma.h"

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

void test()
{
	vsma_t *vsma = (vsma_t *)malloc(500 * sizeof(char));
	vsma = VSMAInit(vsma, 500);
	
	printf("%x\n", *(size_t *)vsma);
	printf("magic number: %x\n", *(size_t *)((char *)vsma + 8) );
	
}

int main()
{
	test();
	
	
	return 0;
}
