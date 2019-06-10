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
int is_before(const void *data, const void *key, const void *params);

void test()
{
	srtl_t *srtl = SrtLCreate(*is_before, NULL);
	printf("%d",SrtLSize(srtl));
	SrtLDestroy(srtl);
}

int is_before(const void *data, const void *key, const void *params)
{
	return(key < data);
}

int main()
{
	test();
	
	return 0;
}
