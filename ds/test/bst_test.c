#include <stdio.h>

#include "../include/bst.h"

#define UNUSED(X) (void) (X)

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

int cmp(const void *current_data, const void *data, const void *params);
int print_list(void *data, const void *arg);
int Test_BSTInsert();
int Test_BSTRemove();
int Test_BSTFind();

int main()
{	
	RUN_TEST(Test_BSTInsert);
	RUN_TEST(Test_BSTRemove);
	RUN_TEST(Test_BSTFind);
	
	return 0;
}

int Test_BSTInsert()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	int a = 5;
	int b = 6;
	int c = 4;
	int n = 0;
	bst_it_t iter1 = NULL;
	bst_it_t iter2 = NULL;
	bst_it_t iter3 = NULL;
	
	bst_t *bst = BSTCreate(cmp, NULL);
	/* test1 */
	res = BSTIsEmpty(bst);	
 	TEST_EQUAL(res, 1);
 	
 	/* test7 */
 	res = BSTCount(bst);	
 	TEST_EQUAL(res, 0);	
 	
 	iter1 = BSTInsert(bst, &a);
 	
 	/* test2 */
 	n= *(int *)BSTGetData(iter1);
 	res = n;	
 	TEST_EQUAL(res, 5);		
 	
	iter2 = BSTInsert(bst, &b);
 	
 	/* test3 */
 	n= *(int *)BSTGetData(iter2);
 	res = n;	
 	TEST_EQUAL(res, 6);	

 	/* test4 */
 	n= *(int *)BSTGetData(BSTBegin(bst));
 	res = n;	
 	TEST_EQUAL(res, 5);	

	iter3 = BSTInsert(bst, &c);
 	
 	/* test5 */
 	n= *(int *)BSTGetData(iter3);
 	res = n;	
 	TEST_EQUAL(res, 4);
 	
 	/* test6 */
 	n= *(int *)BSTGetData(BSTBegin(bst));
 	res = n;	
 	TEST_EQUAL(res, 4);	
 	
 	/* test7 */
 	res = BSTCount(bst);	
 	TEST_EQUAL(res, 3);	
	
	BSTDestroy(bst);
	
	return result;
}

int Test_BSTRemove()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	int a = 5;
	int b = 3;
	int arr[]={20,50,80,60,70,40,30};
	int n = 0;
	bst_t *bst = BSTCreate(cmp, NULL);
	bst_it_t iter1,iter2,iter3,iter4,iter5,iter6,iter7;
	
	iter1 = BSTInsert(bst, &arr[0]);
	iter2 = BSTInsert(bst, &arr[1]);
	iter3 = BSTInsert(bst, &arr[2]);
	iter4 = BSTInsert(bst, &arr[3]);
	iter5 = BSTInsert(bst, &arr[4]);
	iter6 = BSTInsert(bst, &arr[5]);
	iter7 = BSTInsert(bst, &arr[6]);

	
	/* test1 */
	res = BSTIsEmpty(bst);	
 	TEST_EQUAL(res, 0);
	
	/* test2 */
 	res = BSTCount(bst);	
 	TEST_EQUAL(res, 7);	
	
 	/* test3 */
 	n= *(int *)BSTGetData(BSTBegin(bst));
 	res = n;	
 	TEST_EQUAL(res, 20);	
 	
 	/* test4 */
 	n= *(int *)BSTGetData((iter2));
 	res = n;	
 	TEST_EQUAL(res, 50);	 	
 	
 	BSTRemove(iter2);
 	
 	/* test5 */
 	n= *(int *)BSTGetData((iter2));
 	res = n;	
 	TEST_EQUAL(res, 60);
 	
 	/* test6 */
 	n= *(int *)BSTGetData((iter4));
 	res = n;	
 	TEST_EQUAL(res, 70);
 	
 	BSTRemove(iter6);
 	
 	/* test7 */
 	n= *(int *)BSTGetData(iter6);
 	res = n;	
 	TEST_EQUAL(res, 30);
 	
  	BSTRemove(iter6);

	/* test8 */
 	n= *(int *)BSTGetData(iter2);
 	res = n;	
 	TEST_EQUAL(res, 60);
 	
 	/* test9 */
 	res = BSTCount(bst);	
 	TEST_EQUAL(res, 4);	
 	
 	printf("\t");
 	BSTForEach(BSTBegin(bst), BSTEnd(bst), print_list, NULL);
	printf("\n");
	
	BSTDestroy(bst);
	
	return result;
}

int Test_BSTFind()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	int arr[]={20,50,80,60,70,40,30};
	int n = 0;
	bst_t *bst = BSTCreate(cmp, NULL);
	bst_it_t iter1,iter2,iter3,iter4,iter5,iter6,iter7,key;
	
	iter1 = BSTInsert(bst, &arr[0]);
	iter2 = BSTInsert(bst, &arr[1]);
	iter3 = BSTInsert(bst, &arr[2]);
	iter4 = BSTInsert(bst, &arr[3]);
	iter5 = BSTInsert(bst, &arr[4]);
	iter6 = BSTInsert(bst, &arr[5]);
	iter7 = BSTInsert(bst, &arr[6]);
	
	
	/* test1 */
	res = BSTIsEmpty(bst);	
 	TEST_EQUAL(res, 0);
 	
	/* test2 */
	key = BSTFind(bst, &arr[0]);
	n = *((int *)BSTGetData(key));
	res = n;	
 	TEST_EQUAL(res, 20);
 	
 	/* test3 */
	key = BSTFind(bst, &arr[1]);
	n = *((int *)BSTGetData(key));
	res = n;	
 	TEST_EQUAL(res, 50);
	
 	/* test4 */
	key = BSTFind(bst, &arr[2]);
	n = *((int *)BSTGetData(key));
	res = n;	
 	TEST_EQUAL(res, 80);	
	
 	/* test5 */
	key = BSTFind(bst, &arr[3]);
	n = *((int *)BSTGetData(key));
	res = n;	
 	TEST_EQUAL(res, 60);
	
	BSTDestroy(bst);
	
	return result;
}

int cmp(const void *current, const void *data, const void *params)
{
	UNUSED(params);
	if(1 == (*(int*)current > *(int*)data))
	{
		return 1; /* enter left */
	}
	else if(1 == (*(int*)current < *(int*)data))

	{
		return -1; /* enter right */
	}
	return 0;
}

int print_list(void *data, const void *arg)
{
	UNUSED(arg);
    printf("%d->", *(int *)data);   
    return 0;
}
