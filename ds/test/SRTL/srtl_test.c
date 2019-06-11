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

int print_list(void *data, const void *arg)
{
	UNUSED(arg);
    printf("%d->", *(char *)data);   
    return 0;
}

/*void test()
{
	int a = 5;
	int b = 3;
	int c = 10;
	int d = 7;
	int e = 1;
	
	srtl_t *srtl = SrtLCreate((scmp_f)is_before, NULL);
	
	SrtLInsert(srtl, &a);
	printf("NULL->");
	DLLForEach(SrtLBegin(srtl), SrtLEnd(srtl), print_list, srtl);
	printf("NULL\n");
	SrtLInsert(srtl, &b);
	printf("NULL->");
	DLLForEach(SrtLBegin(srtl), SrtLEnd(srtl), print_list, srtl);
	printf("NULL\n");
	SrtLInsert(srtl, &c);
	printf("NULL->");
	DLLForEach(SrtLBegin(srtl), SrtLEnd(srtl), print_list, srtl);
	printf("NULL\n");
	SrtLInsert(srtl, &d);
	printf("NULL->");
	DLLForEach(SrtLBegin(srtl), SrtLEnd(srtl), print_list, srtl);
	printf("NULL\n");
	SrtLInsert(srtl, &e);
	printf("NULL->");
	DLLForEach(SrtLBegin(srtl), SrtLEnd(srtl), print_list, srtl);
	printf("NULL\n");
	
	SrtLPopBack(srtl);
	printf("NULL->");
	DLLForEach(SrtLBegin(srtl), SrtLEnd(srtl), print_list, srtl);
	printf("NULL\n");
	
	SrtLDestroy(srtl);
}*/

void test2()
{
	int a = 1;
	int b = 3;
	int c = 5;
	int d = 8;
	int e = 2;
	int f = 4;
	int g = 6;
	int h = 7;
	
	srtl_t *dest = SrtLCreate((scmp_f)is_before, NULL);
	srtl_t *src = SrtLCreate((scmp_f)is_before, NULL);
	
	SrtLInsert(dest, &a);
	SrtLInsert(dest, &b);
	SrtLInsert(dest, &c);
	SrtLInsert(dest, &d);

	SrtLInsert(src, &e);
	SrtLInsert(src, &f);
	SrtLInsert(src, &g);
	SrtLInsert(src, &h);
	
	SrtLMerge(dest, src);
	printf("NULL->");
	SrtLForEach(SrtLBegin(dest), SrtLEnd(dest), print_list, dest);
	printf("NULL\n");
	printf("NULL->");
	SrtLForEach(SrtLBegin(src), SrtLEnd(src), print_list, src);
	printf("NULL\n");
	
}


int is_before(const void *data, const void *key, const void *params)
{
	UNUSED(params);
	return(*((int *)key) < *((int *)data));
}



int main()
{
	test2();
	
	return 0;
}
