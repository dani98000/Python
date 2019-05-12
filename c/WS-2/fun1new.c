#include <stdio.h>
#include <assert.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RUN_TEST(test)\
if(!test())\
{\
printf(#test " - failed!\n");\
}\
else\
{\
printf(#test " - ok!\n");\
}

int test_strlen();
int test_strcmp();
int test_strcpy();
int test_strncpy();
int test_strcasecmp();
int test_strchr();
int test_strdup1();
int test_strcat();
int test_strncat();
int test_strstr1();
int test_strspn();
int test_RmSpaces();
int test_BigAdd();

int main()
{
	RUN_TEST(test_strlen);
	RUN_TEST(test_strcmp);
	RUN_TEST(test_strcpy);
	RUN_TEST(test_strncpy);
	RUN_TEST(test_strcasecmp);
	RUN_TEST(test_strchr);
	RUN_TEST(test_strdup1);
	RUN_TEST(test_strcat);
	RUN_TEST(test_strncat);
	RUN_TEST(test_strstr1);
	RUN_TEST(test_strspn);
	RUN_TEST(test_RmSpaces);
	RUN_TEST(test_BigAdd);
	
	return 0;
}

int test_strlen()
{
	return(sstrlen("Hello") == 5 && sstrlen("") == 0 && sstrlen(" ") == 1) ;
}

int test_strcmp()
{
	return(str_cmp("cello", "cello") == 0 && str_cmp("aaa", "bbbbbbb") < 0 && str_cmp("b", "aaaaaaaaaaaaa") > 0);
}

int test_strcpy()
{
	char dest[5];
	str_cpy(dest, "hey");
	return(str_cmp(dest, "hey") == 0);
}

int test_strncpy()
{
	char dests[10];
	strn_cpy(dests, "hey", 3);
	return(str_cmp(dests, "hey") == 0);
}

int test_strcasecmp()
{
	return(strcasecmp("hey", "HEY") == 0);
}

int test_strchr()
{
	char *s1 = "hello";
	
	return(*strchr(s1, 'e') == *(s1 + 1));
}

int test_strdup1()
{
	char *a;
	char *b = "hello";
	int result;
	a = strdup(b);
	result = str_cmp(a, b);
	free(a);
	
	return(result == 0);
}

int test_strcat()
{
	char src1[] = "hey";
	char src2[] = "there";
	char dest1[100] = "";
	char dest2[100] = "";
	char eran[10] = "eran";
	char* a = strcat(dest1, src1);
	char* b = strcat1(dest2, src1);
	char ben[] = {'\0','\0','\0','\0','\0','\0'};
	char ben2[] = {'h','e','l','l','o'};
	
	a = strcat(dest1, src2);
	b = strcat1(dest2, src2);

	return(strcmp(a,b) == 0 && strcat(ben,ben2) == strcat1(ben,ben2) && 0 == str_cmp(strcat1(eran, src1), "eranhey"));
}

int test_strncat()
{
	char src[10] = "you";
	char dest[10] = "fuck";
	return(0 == str_cmp(strncat1(dest,src,1), "fucky"));
}

int test_strstr1()
{
	char haystack[10] = "yohoyo";
	char needle[10] = "ho";
	char haystack1[20] = "sssssssssssssss";
	char needle1[10] ="d";
	return (strstr1(haystack, needle) == haystack + 2 && strstr1(haystack1, needle1) == NULL);
}

int test_strspn()
{
	char s[10] = "abcdeqs";
	char accept[10] = "abc";
	return(strspn1(s, accept) == 3); 
}

int test_RmSpaces()
{
	char str[]="         hey there       yo";
	char str2[]="         hey there       yo  ";
	char str3[]="hey there       yo  ";
	RmSpaces(str);
	RmSpaces(str2);
	RmSpaces(str3);
	return(!isspace(*str) && !isspace(*(str+strlen(str))) && strstr(str,"  ") == NULL
			&& !isspace(*str2) && !isspace(*(str2+strlen(str2))) && strstr(str2,"  ") == NULL
			&& 	!isspace(*str3) && !isspace(*(str3+strlen(str3))) && strstr(str3,"  ") == NULL);
}

int test_BigAdd()
{
	char num1[] = {'0','9','9','9','9','\0'};
	char num2[] = {'0','0','9','9','9','\0'};
	char str[] = {'0','0','0','0','0','\0'};
	printf("%s\n",BigAdd(num1,num2,str));
	printf("%s\n",num2);
	printf("%s\n",num1);
	return(0) ;
}
