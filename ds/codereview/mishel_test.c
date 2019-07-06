#include <stdlib.h> /* size_t */
#include <stdio.h> /* size_t */
#include <string.h> /*strcmp*/
#include <errno.h> /* errno */
#include <unistd.h> /* access */
#include <time.h> /* time_t */

#include "../include/bst.h" /* Scd header */
/*#include "../src/bst.c"*/ /* Scd header */

#define RUN_TEST(test) \
if(test()){ printf("\033[1;32m%-24s\t| %5s\n\033[0m", "["#test"]","OK!\n"); } \
else{ printf("\x1B[31m%-24s| %7s\n\033[0m", "["#test"]", "FAIL!\n"); }

#define SUCCESS (0)
#define FAILURE (1)	

#define PRINTOK printf("\033[1;32m%-24s\t \n\033[0m","\t|  OK!\n")
#define PRINTFAIL printf("\x1B[31m%-24s \n\033[0m", "\t|  FAIL!\n")
#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m\x1b[1m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"
#define UNUSED(X) (void)(X)

/*
void PrintBst(bst_t *bst)
{
	bst_it_t current = BSTBegin(bst);
	bst_it_t end = BSTEnd(bst);
	
	while(current != end)
	{
		current = BSTNext
	}
}
*/
int IsBigger(const void *current, const void *data, const void *params)
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

int action(void *data, const void *args)
{
	*(int*)data = 50;
	UNUSED(args);
	
	return 50 == *(int*)data;
}

int BSTCreateTest()
{
	int result = 1;
	
	bst_t *bst = BSTCreate(IsBigger, NULL);	
	if(NULL == bst)
	{
		result = 0;
	}
		
	return result;
}

int BSTInsertNextPrevFindTest()
{
	int result = 1, test_num = 0;
	size_t res = 0, expected = 0;
	void *data = (void*)malloc(16);
	void *data2 = (void*)malloc(16);
	void *data3 = (void*)malloc(16);
	bst_it_t current = NULL;
	bst_it_t current1 = NULL;
	bst_it_t end = NULL;
	bst_t *bst = BSTCreate(IsBigger, NULL);	
	if(NULL == bst)
	{
		return 0;
	}
	end = BSTEnd(bst);
	
	/*test 1*/ 
	++test_num;
	*(int*)data = 70;
	
	printf("count = %d\n",BSTCount(bst));
	
	current1  = BSTInsert(bst, data);
	
	printf("count = %d\n",BSTCount(bst));
	res = NULL == current1;
	expected = 0;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;

	/*test 2*/ 
	++test_num;
	
	res = 70 == *(int*)BSTGetData(current1);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/*test 3*/ 
	++test_num;
	*(int*)data2 = 30;
	
	current  = BSTInsert(bst, data2);
	printf("count = %d\n",BSTCount(bst));
	res = NULL == current;
	expected = 0;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;

	/*test 4*/ 
	++test_num;
	
	res = 30 == *(int*)BSTGetData(current);
	res *= current == BSTFind(bst, data2);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/*test 5*/ 
	++test_num;
	*(int*)data3 = 77777777;
	
	current  = BSTInsert(bst, data3);
	
	printf("count = %d\n",BSTCount(bst));
	res = NULL == current;
	expected = 0;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;

	/*test 6*/ 
	++test_num;
	
	
	
	res = 77777777 == *(int*)BSTGetData(current);
	res *= 3 == BSTCount(bst);
	res *= current == BSTFind(bst, data3);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 7 */
	++test_num;
	
	res = 0xdeadbeef == (size_t)BSTGetData(BSTNext(current));
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;	
	
	/* test 8 */
	++test_num;
	
	res = 70 == *(int*)BSTGetData(BSTPrev(current));
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 9 */
	++test_num;
	
	BSTRemove(current);
	
	printf("count = %d\n",BSTCount(bst));
	
	res = 2 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 10 */
	++test_num;
	*(int*)data3 = 77777777;
		
	current = BSTInsert(bst, data3);
	printf("count = %d\n",BSTCount(bst));
	
	BSTRemove(current1);
	
	printf("count = %d\n",BSTCount(bst));
	res *= end == BSTFind(bst, data);
	res = 2 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 11 */
	++test_num;

	BSTDestroy(bst);
	
	res = BSTCount(bst);
	res *= end == BSTFind(bst, data2);
	expected = 0;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	free(data);
	free(data2);
	free(data3);
	
	return result;
}

int BSTForEachTest()
{
	int result = 1, test_num = 0;
	size_t res = 0, expected = 0;
	void *data1 = (void*)malloc(16);
	void *data2 = (void*)malloc(16);
	void *data3 = (void*)malloc(16);
	bst_it_t current1 = NULL;
	bst_it_t current2 = NULL;
	bst_it_t current3 = NULL;
	bst_it_t end = NULL;
	bst_t *bst = BSTCreate(IsBigger, NULL);	
	if(NULL == bst)
	{
		return 0;
	}
	end = BSTEnd(bst);
	
	/*test 1*/ 
	++test_num;
	*(int*)data1 = 70;
	*(int*)data2 = 30;
	*(int*)data3 = 777;
	
	current1  = BSTInsert(bst, data1);
	current2  = BSTInsert(bst, data2);
	current3  = BSTInsert(bst, data3);
	res = 0 == BSTForEach(current2, current3, action, NULL);  
	expected = 1;
	
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	
	/*test 1*/ 
	++test_num;
	
	res = 50 == *(int*)BSTGetData(current1);  
	res *= 50 == *(int*)BSTGetData(current2);  
	res *= 777 == *(int*)BSTGetData(current3);  
	expected = 1;
	
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/*test 2*/ 
	++test_num;
	res = 0 == BSTForEach(current3, end, action, NULL);  
	
	res = 50 == *(int*)BSTGetData(current1);  
	res *= 50 == *(int*)BSTGetData(current2);  
	res *= 50 == *(int*)BSTGetData(current3);  
	expected = 1;
	
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;

	/* test 3 */
	++test_num;

	BSTDestroy(bst);
	
	res = BSTCount(bst);
	res *= end == BSTFind(bst, data2);
	expected = 0;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	free(data1);
	free(data2);
	free(data3);
	
	return result;
}

void PrintArr(bst_t *bst, int *arr)
{
	bst_it_t current = BSTBegin(bst);
	bst_it_t end = BSTEnd(bst);
	int *arr_runn = arr;

	printf(CYAN"Current arr: [");	
	while(current != end)
	{
		*arr_runn = *(int*)BSTGetData(current);
		printf("%d,", *arr_runn);
		++arr_runn;
		current = BSTNext(current);
	}
	printf("]\n");
}

int BSTFlowTest()
{
	int result = 1, test_num = 0;
	size_t res = 0, expected = 0;
	void *n50 = (void*)malloc(16);
	void *n25 = (void*)malloc(16);
	void *n75 = (void*)malloc(16);
	void *n10 = (void*)malloc(16);
	void *n40 = (void*)malloc(16);
	void *n60 = (void*)malloc(16);
	void *n30 = (void*)malloc(16);
	void *n1 = (void*)malloc(16);
	void *n15 = (void*)malloc(16);
	void *n11 = (void*)malloc(16);
	void *n26 = (void*)malloc(16);
	void *n35 = (void*)malloc(16);
	void *n65 = (void*)malloc(16);
	void *n64 = (void*)malloc(16);
	void *n70 = (void*)malloc(16);
	void *n72 = (void*)malloc(16);
	void *n67 = (void*)malloc(16);
	void *n68 = (void*)malloc(16);
	void *n66 = (void*)malloc(16);
	int arr[] = {1,10,11,15,25,26,30,35,40,50,60,64,65,66,67,68,70,72,75};
	int arr2[] = {1,10,11,15,25,26,30,40,50,60,64,65,66,67,68,70,72,75};
	int arr3[] = {1,10,11,15,25,26,40,50,60,64,65,66,67,68,70,72,75};
	int arr4[] = {10,11,15,25,26,40,50,60,64,65,66,67,68,70,72,75};	
	int arr5[] = {10,11,25,26,40,50,60,64,65,66,67,68,70,72,75};	
	int arr6[] = {10,11,25,26,40,50,60,64,66,67,68,70,72,75};	
	int arr7[] = {10,11,25,26,40,60,64,66,67,68,70,72,75};	
	int *arr_curr = (int*)malloc(20*8);
	bst_it_t from = NULL;
	bst_it_t current1 = NULL;
	bst_it_t current2 = NULL;
	bst_it_t current3 = NULL;
	bst_it_t current4 = NULL;
	bst_it_t current5 = NULL;
	bst_it_t current6 = NULL;	
	bst_it_t end = NULL;
	bst_t *bst = BSTCreate(IsBigger, NULL);	
	if(NULL == bst)
	{
		return 0;
	}
	end = BSTEnd(bst);
	
	/*test 1*/ 
	++test_num;
	
	*(int*)n50 = 50;
	*(int*)n25 = 25;
	*(int*)n75 = 75;
	*(int*)n10 = 10;
	*(int*)n40 = 40;
	*(int*)n60 = 60;
	*(int*)n30 = 30;
	*(int*)n1 = 1;
	*(int*)n15 = 15;
	*(int*)n11 = 11;
	*(int*)n26 = 26;
	*(int*)n35 = 35;
	*(int*)n65 = 65;
	*(int*)n64 = 64;
	*(int*)n70 = 70;
	*(int*)n72 = 72;
	*(int*)n67 = 67;
	*(int*)n68 = 68;
	*(int*)n66 = 66;
	
	current6 = BSTInsert(bst, n50);
	BSTInsert(bst, n25);
	BSTInsert(bst, n75);
	BSTInsert(bst, n10);
	BSTInsert(bst, n40);
	BSTInsert(bst, n60);
	current2 = BSTInsert(bst, n30);
	current3 = BSTInsert(bst, n1);
	current4 = BSTInsert(bst, n15);
	BSTInsert(bst, n11);
	BSTInsert(bst, n26);
	current1 = BSTInsert(bst, n35);
	current5 = BSTInsert(bst, n65);
	BSTInsert(bst, n64);
	BSTInsert(bst, n70);
	BSTInsert(bst, n72);
	BSTInsert(bst, n67);
	BSTInsert(bst, n68);
	BSTInsert(bst, n66);
	
	PrintArr(bst, arr_curr);
	res = 0 == memcmp(arr, arr_curr, 76);
	res *= 19 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 2 */
	++test_num;

	BSTRemove(current1);
	PrintArr(bst, arr_curr);
	res = 0 == memcmp(arr2, arr_curr, 72);
	res *= 18 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 3 */
	++test_num;

	BSTRemove(current2);
	PrintArr(bst, arr_curr);
	res = 0 == memcmp(arr3, arr_curr, 68);
	res *= 17 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 4 */
	++test_num;

	BSTRemove(current3);
	PrintArr(bst, arr_curr);
	res = 0 == memcmp(arr4, arr_curr, 64);
	res *= 16 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 5 */
	++test_num;

	BSTRemove(current4);
	PrintArr(bst, arr_curr);
	res = 0 == memcmp(arr5, arr_curr, 60);
	res *= 15 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;

	/* test 6 */
	++test_num;

	BSTRemove(current5);
	PrintArr(bst, arr_curr);
	res = 0 == memcmp(arr6, arr_curr, 56);
	res *= 14 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	/* test 7 */
	++test_num;

	BSTRemove(current6);
	PrintArr(bst, arr_curr);
	res = 0 == memcmp(arr7, arr_curr, 52);
	res *= 13 == BSTCount(bst);
	expected = 1;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
				
	/* test 8 */
	++test_num;

	BSTDestroy(bst);

	free(n50);
	free(n25);
	free(n75);
	free(n10);
	free(n40);
	free(n60);
	free(n30);
	free(n1);
	free(n15);
	free(n11);
	free(n26);
	free(n35);
	free(n65);
	free(n64);
	free(n70);
	free(n72);
	free(n67);
	free(n68);
	free(n66);
	free(arr_curr);
	
	res = BSTCount(bst);
	expected = 0;
	result = expected == res;
	printf(MAGENTA"test :%d expected :%ld result: %ld", test_num, expected, res);
	result == 1 ? PRINTOK : PRINTFAIL;
	
	return result;
}
int main()
{
	RUN_TEST(BSTCreateTest);
	RUN_TEST(BSTInsertNextPrevFindTest);
	RUN_TEST(BSTForEachTest);
	RUN_TEST(BSTFlowTest)
	
	return 1;
}
