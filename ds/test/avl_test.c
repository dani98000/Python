#include "../include/avl.h"

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

int cmp(const void *current, const void *data, const void *params);
int print_list(void *data, const void *arg);
int IsSorted(int *arr, int size);
int Test_Insert();
int Test_Balance();
int Test_Remove();
int Stress_Test();

int main()
{
	/*avl_t *tree = AVLCreate(cmp ,NULL);
	avl_node_t *node = NULL;
	int a = 5;
	int b = 7;
	int c = 4;
	int d = 1;
	int x = 0;
	int e = 3;
	int w = 20;
	int n = 18;
	int z = 6;
	int key = 5;
	int size = 0;
	int res = 0;
	
	AVLInsert(tree, &a);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &d);
	AVLInsert(tree, &x);	
	AVLInsert(tree, &e);
	AVLInsert(tree, &w);
	AVLInsert(tree, &n);
	AVLInsert(tree, &z);
	
	AVLRemove(tree, &key);
	
	AVLForEach(tree,print_list, NULL);
	printf("\n");
	
	size = AVLSize(tree);
	printf("size = %d\n", size);
	/*res = *(int *)AVLFind(tree, &key);*/
/*	printf("should print 1: %d\n",*(int *)AVLFind(tree, &key));
	
	AVLDestroy(tree);*/
	RUN_TEST(Test_Insert);
	RUN_TEST(Test_Balance);
	RUN_TEST(Test_Remove);
	RUN_TEST(Stress_Test);
	
	return 0;
}

int Test_Insert()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *tree = AVLCreate(cmp ,NULL);
	int a = 5;
	int b = 7;
	
	/* TEST1 */
	res = AVLSize(tree);
	TEST_EQUAL(res, 0);
	
	/* TEST2 */
	res = AVLIsEmpty(tree);
	TEST_EQUAL(res ,1);
	
	AVLInsert(tree, &a);
	
	/* TEST3 */
	res = AVLSize(tree);
	TEST_EQUAL(res, 1);
	
	/* TEST4 */
	res = AVLIsEmpty(tree);
	TEST_EQUAL(res ,0);
	
	AVLInsert(tree, &b);
	
	/* TEST5 */
	res = AVLSize(tree);
	TEST_EQUAL(res, 2);
	
	AVLDestroy(tree);
		
	return result;
}

int Test_Balance()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *tree = AVLCreate(cmp ,NULL);
	int a = 5;
	int b = 10;
	int c = 15;
	int d = 20;	

	
	AVLInsert(tree, &a);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &d);
	
	/* TEST1 */
	res = AVLSize(tree);
	TEST_EQUAL(res, 4);
	
	/* TEST2 */
	res = AVLGetHeight(tree);
	TEST_EQUAL(res, 2);
	
	return result;
	
	AVLDestroy(tree);
}

int Test_Remove()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *tree = AVLCreate(cmp ,NULL);
	int a = 5;
	int b = 7;
	int c = 4;
	int d = 1;
	int x = 0;
	int e = 3;
	int w = 20;
	int n = 18;
	int z = 6;
	int key = 4;
	int key2 = 7;	
	
	AVLInsert(tree, &a);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &d);
	AVLInsert(tree, &x);	
	AVLInsert(tree, &e);
	AVLInsert(tree, &w);
	AVLInsert(tree, &n);
	AVLInsert(tree, &z);
	

	
	
	/* TEST1 */
	res = AVLSize(tree);
	TEST_EQUAL(res, 9);
	
	/*AVLRemove(tree, &key);*/
	AVLRemove(tree, &key2);
	
	AVLForEach(tree,print_list, NULL);
	printf("\n");
	
	AVLDestroy(tree);
	
	return result;
}

int Stress_Test()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	int randomIndex = 0;
	int temp = 0;
	int i = 0;
	avl_t *tree = AVLCreate(cmp ,NULL);
	int arr[50000];

	
	for(i = 0; i < 50000; i++) 
	{
    	arr[i] = i;
	}

	for(i = 0; i < 50000; i++) 
	{   
    	temp = arr[i];
   		randomIndex = rand() % 50000;

   		arr[i] = arr[randomIndex];
    	arr[randomIndex] = temp;
	}

	for(i = 0; i < 50000; i++) 
	{   
		AVLInsert(tree, &arr[i]);
	}
	
	AVLForEach(tree,print_list, NULL);
	printf("\n");
	

	
	return result;
}	

int cmp(const void *current, const void *data, const void *params)
{
	UNUSED(params);
	if((*(int*)current > *(int*)data))
	{
		return 1; /* enter left */
	}
	else if((*(int*)current < *(int*)data))

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
