#include <stdio.h>
#include <stdlib.h>
#include "../include/recursion.h"

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

size_t g_total_tests = 0;
size_t g_total_success = 0;
size_t g_total_failed = 0;

int Test_FibRec();
int Test_FibIter();
int Test_strlen();
int Test_strcmp();
int Test_strcpy();
int Test_flip();
int Test_stack();

int main()
{
	RUN_TEST(Test_FibRec);
	RUN_TEST(Test_FibIter);
	RUN_TEST(Test_strlen);
	RUN_TEST(Test_strcmp);
	RUN_TEST(Test_strcpy);	
	RUN_TEST(Test_flip);	
	RUN_TEST(Test_stack);	
	
	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	
	return 0;
}

int Test_FibRec()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	
	res = FibRec(5);
	TEST_EQUAL(res, 8);
	
	return result;
}

int Test_FibIter()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	
	res = FibIter(5);
	TEST_EQUAL(res, 8);
	
	return result;
}

int Test_strlen()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	char *str = "daniel";

	res = str_len(str);
	
	TEST_EQUAL(res, 6);
	
	return result;
}

int Test_strcmp()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	char *str1 = "daniel";
	char *str2 = "daniel";
	char *str3 = "abcd";
	char *str4 = "abce";
	
	res = str_cmp(str1,str2);
	TEST_EQUAL(res, 0);
	
	res = str_cmp(str3,str4);
	TEST_EQUAL(res, -1);
	
	return result;
}

int Test_strcpy()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	char *str1 = "daniel";
	char str2[] = "      ";
	
	str_cpy(str2,str1);
	res = str_cmp(str1,str2);
	
	TEST_EQUAL(res, 0);
	
	return result;
}

int Test_flip()
{
	int i = 0;
	int j = 0;
	node_t *current = NULL;
	node_t *list = (node_t *)malloc(sizeof(node_t) * 5);
	
	int arr[] = {1,2,3,4,5};
	
	for(; i < 4; ++i)
	{	
		(list + i)->next = list + i + 1;
		(list + i)->data = (int *)arr[i];
	}
	
	(list + 4)->next = NULL;
	(list + 4)->data = (int *)arr[4];
	
	current = RecurFlip(list);

	while(current != NULL)
	{
		printf("%d->", (int *)current->data);
		current = current->next;
	}	
	
	return 1;
}

int Test_stack()
{
	stack_t *stack = STACKCreate(3, sizeof(int)); 
	int a = 1;
	int b = 10;
	int c = 5;	
	int n = 0;
	
	int result = 1;
	STACKPush(stack, &a); 
	STACKPush(stack, &b); 
	STACKPush(stack, &c); 
	
	RecurStackSort(stack);
		
	n = *((int *)STACKPeek((void *)stack)); 
	printf("%d\n",n);
	
		printf("size = %d\n",STACKSize(stack));
	
	
	
	STACKPop(stack);
	n = *((int *)STACKPeek((void *)stack)); 
	printf("%d\n",n);
		
	
	
	result *= (n == 1);
	
	return result;
}
