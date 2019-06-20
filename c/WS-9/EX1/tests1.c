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

int test_memset(void);
int test_memcpy(void);
int test_memmove(void);

int main() 
{
	printf("Test Results:\n");
	RUN_TEST(test_memset);
	RUN_TEST(test_memcpy);
	RUN_TEST(test_memmove);
	printf("\n");
	if(test_memset() && test_memcpy() && test_memmove())
	{
		printf("\033[1;32m|All Tests were Passed Successfuly| \033[0m\n");
	}
	
	return 0;
}

int test_memset(void)
{
	char *s = NULL;
	int result = 1;

	s = calloc(50, sizeof(char));
	if(NULL == s)
	{
		printf("memory allocation error");
		return 0;
	}

	memsetV2(s, 'a', 10);
	result *= (0 == strcmp(s, "aaaaaaaaaa"));

	memsetV2(s, 'b', 2);
	result *= (0 == strcmp(s, "bbaaaaaaaa"));
	
	memsetV2(s + 2, 'b', 12);
	result *= (0 == strcmp(s + 2, "bbbbbbbbbbbb"));

	memsetV2(s + 6, '1', 10);
	result *= (0 == strcmp(s + 6, "1111111111"));

	memsetV2(s + 16, '5', 1);
	result *= (0 == strcmp(s + 16, "5"));

	memsetV2(s + 18, '5', 0);
	result *= (0 == strcmp(s + 18, ""));
	
	free(s);

	return result;
}


int test_memcpy(void)
{
	char *dest = NULL, *src = NULL;
	int result = 1;

	dest = calloc(50, sizeof(char));
	if(NULL == dest)
	{
		printf("memory allocation error");
		return 0;
	}

	src = calloc(50, sizeof(char));
	if(NULL == src)
	{
		printf("memory allocation error");
		return 0;
	}

	strcpy(src, "My Name Is Daniel! yooo");

	memcpyV2(dest, src, 5);
	result *= (0 == strcmp(dest, "My Na"));

	memcpyV2(dest, src, 9);
	result *= (0 == strcmp(dest, "My Name I"));

	memcpyV2(dest + 17, src + 1, 0);
	result *= (0 == strcmp(dest + 17, ""));
	
	memcpyV2(dest + 4, src + 1, 13);
	result *= (0 == strcmp(dest + 4, "y Name Is Dan"));


	free(dest);
	free(src);
	
	return result;
}

int test_memmove(void)
{
	char *src = NULL;
	int result = 1;

	src = calloc(100, sizeof(char));
	if(NULL == src)
	{
		perror("memory allocation error");
		return 0;
	}

	strcpy(src, "abcdefg");
	
	memmoveV2(src+5, src, 2);
	result *= (0 == strcmp(src, "abcdeab"));

	memmoveV2(src+2, src, 5);
	result *= (0 == strcmp(src, "ababcde"));
	
	memmoveV2(src, src, strlen(src));
	result *= (0 == strcmp(src, "ababcde"));

	free(src);
	
	return result;
}
