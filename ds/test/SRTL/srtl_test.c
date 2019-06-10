#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "../../include/SRTL/srtl.h"

#define UNUSED(X) (void) (X)

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
int is_before(const void *data, const void *key);

void test()
{
	int a = 5;
	srtl_t *srtl = SrtLCreate(is_before, NULL);
	printf("before insert:%lu\n",SrtLSize(srtl));	
	SrtLInsert(srtl, &a);
	printf("after insert:%lu\n",SrtLSize(srtl));
	SrtLDestroy(srtl);
}

int is_before(const void *data, const void *key)
{
	return(key < data);
}

int main()
{
	test();
	
	return 0;
}
