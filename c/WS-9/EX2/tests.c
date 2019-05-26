/************************************
*									*
*		Author: Daniel Maizel		*
*		Reviewer: 					*
*		Date: 26/05/2019			*
*									*					
*									*
************************************/



#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */
#include <string.h>	/* strcpy */

#include "functions.h"

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

int test_itoa();
int test_atoi();
int test_itoa2();
int test_atoi2();

int main() 
{
	printf("Test Results:\n");
	
	RUN_TEST(test_itoa);
	RUN_TEST(test_atoi);
	RUN_TEST(test_itoa2);	
	RUN_TEST(test_atoi2);
	
	printf("\n");
	if(test_itoa() && test_atoi() && test_itoa2() && test_atoi2())
	{
		printf("\033[1;32m|All Tests were Passed Successfuly| \033[0m\n");
	}
	
	return 0;
}

int test_itoa()
{
	int result = 1;
	char *p =(char *)malloc(100*sizeof(char));
	
	MyItoa(5, p);
	result *= (0 == strcmp(p, "5"));
	
	MyItoa(-5, p);
	result *= (0 == strcmp(p, "-5"));
	
	MyItoa(0, p);
	result *= (0 == strcmp(p, "0"));
	
	free(p);
	
	return result;
}

int test_atoi()
{
	int result = 1;
	
	result *= MyAtoi("158") == 158;
	result *= MyAtoi("-158") == -158;
	result *= MyAtoi("0") == 0;
	
	return result;
}

int test_itoa2()
{
	int result = 1;
	char *p =(char *)malloc(100*sizeof(char));
	
	MyItoaV2(17,p,16); 
	result *= (0 == strcmp(p, "11"));
	
	MyItoaV2(15,p,2); 
	result *= (0 == strcmp(p, "1111"));
	
	MyItoaV2(31,p,16); 
	result *= (0 == strcmp(p, "1F"));
	
	MyItoaV2(-31,p,10); 
	result *= (0 == strcmp(p, "-31"));
	
	free(p);
	
	return result;
}

int test_atoi2()
{
	int result = 1;
	
	result *= MyAtoiV2("1111",2) == 15;
	result *= MyAtoiV2("1F",16) == 31;
	result *= MyAtoiV2("-185",10) == -185;
	result *= MyAtoiV2("11",16) == 17;
	
	return result;
}
