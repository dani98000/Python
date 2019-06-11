#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "../../include/PQ/pq.h"

#define UNUSED(X) (void) (X)

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
int is_before(const void *data, const void *key, const void *params);

int print_list(void *data, const void *arg)
{
	UNUSED(arg);
    printf("%d->", *(char *)data);   
    return 0;
}

int ShouldErase(const void *data, const void *key, const void *params)
{
	return (*((int *)data) == *((int *)key));
}

int Test_EnqueueDequeue();
int Test_Clear();
int Test_Erase();

int main()
{
	RUN_TEST(Test_EnqueueDequeue);
	RUN_TEST(Test_Clear);
	RUN_TEST(Test_Erase);	
	return 0;
}

int is_before(const void *data, const void *key, const void *params)
{
	UNUSED(params);
	return(*((int *)key) < *((int *)data));
}



int Test_EnqueueDequeue()
{
	pq_t *pq = NULL;
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	int a = 5;
	int b = 8;
	int c = 6;
	
	pq = PQCreate((pqcmp_f)is_before);
	
	/* test 1 */
	PQEnqueue(pq, &a);
	res = *((int *)PQPeek(pq));
	TEST_EQUAL(res,5);
	
	/* test 2 */
	PQEnqueue(pq, &b);
	res = *((int *)PQPeek(pq));
	TEST_EQUAL(res,8);
	
	/* test 3 */
	PQEnqueue(pq, &c);
	res = *((int *)PQPeek(pq));
	TEST_EQUAL(res,8);
	
	/* test 4 */
	PQDequeue(pq);
	res = *((int *)PQPeek(pq));
	TEST_EQUAL(res,6);
	
	/* test 5 */
	res = PQSize(pq);
	TEST_EQUAL(res,2);
	
	/* test 6 */
	PQDequeue(pq);
	res = PQIsEmpty(pq);
	TEST_EQUAL(res,0);
	
	/* test 7 */
	PQDequeue(pq);
	res = PQIsEmpty(pq);
	TEST_EQUAL(res,1);
	
	PQDestroy(pq);
	
	return result;	
}

int Test_Clear()
{
	pq_t *pq = NULL;
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	int a = 5;
	int b = 8;
	int c = 6;
	
	pq = PQCreate((pqcmp_f)is_before);
	
	/* test 1 */
	PQEnqueue(pq, &a);
	PQEnqueue(pq, &b);
	PQEnqueue(pq, &c);
	
	/* test 5 */
	res = PQSize(pq);
	TEST_EQUAL(res,3);
	
	/* test 4 */
	PQClear(pq);
	res = PQSize(pq);
	TEST_EQUAL(res,0);
		
	PQDestroy(pq);
	
	return result;	
}

int Test_Erase()
{
	pq_t *pq = NULL;
	int result = 1;
	size_t test_no = 0;
	int res = 0;
	int a = 5;
	int b = 8;
	int c = 5;
	int d = 5;
	int e = 10;
	int key = 5;
	
	pq = PQCreate((pqcmp_f)is_before);
	
	PQEnqueue(pq, &a);
	PQEnqueue(pq, &b);
	PQEnqueue(pq, &c);
	PQEnqueue(pq, &d);
	PQEnqueue(pq, &e);
	
	/* test 1 */
	res = PQSize(pq);
	TEST_EQUAL(res, 5);
	
	/* test 2 */
	res = PQErase(pq, &key, ShouldErase);
	TEST_EQUAL(res, 3);
	
	/* test 3 */
	res = PQSize(pq);
	TEST_EQUAL(res, 2);
	
	/* test 4 */
	PQDequeue(pq);
	res = *((int *)PQPeek(pq));
	TEST_EQUAL(res, 8);
			
	PQDestroy(pq);
	
	return result;	
}
