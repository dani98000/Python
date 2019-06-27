#include <stdio.h>  /* printf */
#include <stdlib.h> /* */
#include <errno.h>  /* errno  */

#include "../include/cbuf.h"

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

int Test_Write(void);
int Test_Read(void);
int Test_Capacity(void);
int Test_IsEmpty(void);
int Test_ReadWrite(void);

int main()
{	
	RUN_TEST(Test_Write);
	RUN_TEST(Test_Read);
	RUN_TEST(Test_Capacity);
	RUN_TEST(Test_IsEmpty);
	RUN_TEST(Test_ReadWrite);
	
	return 0;
}

int Test_Write(void)
{
	cbuf_t *cbuf = NULL;
	int result = 1;
	size_t test_no = 0;
	size_t capacity = 4;
	int res = 0;
	char *string = "Daniel";
	
	cbuf = CBUFCreate(capacity);
	
	/* test 1 */
	res = CBUFWrite(cbuf, string, 1);
	TEST_EQUAL(res,1);
	
	/* test 2 */
	res = CBUFWrite(cbuf, string ,2);
	TEST_EQUAL(res,2);
	
	/* test 3 */
	res = CBUFFreeSpace(cbuf);
	TEST_EQUAL(res,1);
	
	/* test 4 */
	res = CBUFWrite(cbuf, string ,1);
	TEST_EQUAL(res,1);
	
	/* test 5 */
	TEST_EQUAL(errno, EOVERFLOW);

	CBUFDestroy(cbuf);
	
	return result;
}

int Test_Read(void)
{
	cbuf_t *cbuf = NULL;
	int result = 1;
	size_t test_no = 0;
	size_t capacity = 11;
	int res = 0;
	char dest[] = {0,0,0,0,0,0,0,0,0,0,0};
	char *string = "HelloWorld";
	
	cbuf = CBUFCreate(capacity);
	CBUFWrite(cbuf, string, 11);
	
	/* test1 */
	res = CBUFFreeSpace(cbuf);
	TEST_EQUAL(res, 0);
	
	/* test2 */
	res = CBUFRead(cbuf, dest, 5);
	TEST_EQUAL(res, 5);
	
	/* test3 */
	res = CBUFFreeSpace(cbuf);
	TEST_EQUAL(res, 5);
	
	/* test4 */
	res = strcmp(dest, "Hello");
	TEST_EQUAL(res, 0);
	
	/* test5 */
	res = CBUFRead(cbuf, dest, 6);
	TEST_EQUAL(res, 6);
	
	/* test6 */ 
	res = strcmp(dest, "World");
	TEST_EQUAL(res, 0);
	
	/* test7 */
	res = CBUFFreeSpace(cbuf);
	TEST_EQUAL(res, 11);
	
	/* test8 */
	TEST_EQUAL(errno, ENODATA);
	
	CBUFDestroy(cbuf);
	return(result);
}	

int Test_Capacity()
{
	cbuf_t *cbuf = NULL;
	int result = 1;
	size_t test_no = 0;
	size_t capacity = 10;
	int res = 0;
	
	cbuf = CBUFCreate(capacity);
	
	/* test1 */
	res = CBUFCapacity(cbuf);
	TEST_EQUAL(res, 10);
	
	CBUFDestroy(cbuf);
	return(result);
}

int Test_IsEmpty(void)
{
	cbuf_t *cbuf = NULL;
	int result = 1;
	size_t test_no = 0;
	size_t capacity = 10;
	int res = 0;
	char *string = "HelloWorld";

	cbuf = CBUFCreate(capacity);
	
	/* test1 */
	res = CBUFIsEmpty(cbuf);
	TEST_EQUAL(res, 1);
	
	/* test2*/
	CBUFWrite(cbuf, string, 2);
	res = CBUFIsEmpty(cbuf);
	TEST_EQUAL(res, 0);	
	
	CBUFDestroy(cbuf);
	
	return result;
}
int Test_ReadWrite(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	size_t capacity = 11;
	cbuf_t *cbuf = NULL;
	char *string = "HelloWorld";
	char dest[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	cbuf = CBUFCreate(capacity);	
	CBUFWrite(cbuf, string, 11);

	/* test1 */
	res = CBUFFreeSpace(cbuf);
	TEST_EQUAL(res, 0);

	/* test2 */
	res = CBUFRead(cbuf, dest, 11);
	TEST_EQUAL(res, 11);

	/* test3 */
	res = strcmp(dest, "HelloWorld");
	TEST_EQUAL(res, 0);

	CBUFWrite(cbuf, "12345", 6);

	/* test4 */
	res = CBUFFreeSpace(cbuf);
	TEST_EQUAL(res, 5);
	
	/* test5 */
	res = CBUFRead(cbuf, dest, 6);
	TEST_EQUAL(res, 6);

	/* test6 */
	res = strcmp(dest, "12345");
	TEST_EQUAL(res, 0);

	/* test7 */
	res = CBUFIsEmpty(cbuf);
	TEST_EQUAL(res, 1);

	/* test8 */
	res = CBUFRead(cbuf, dest, 5);
	TEST_EQUAL(res, 0);
	
	CBUFDestroy(cbuf);

	return result;
}
