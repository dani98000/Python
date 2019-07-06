#include <stdlib.h> /* size_t */
#include <stdio.h> /* size_t */

#include "../include/bst.h"

#define RUN_TEST(test) \
{ \
if (!test) \
{ printf("\033[1;32m  -OK\033[0m\n"); } \
else \
{ printf("\033[1;31m  -ERROR\033[0m\n"); } \
}

int TestCreate();
int TestFlow();
int TestRandom();

int main()
{
    /*RUN_TEST(TestCreate());*/
    RUN_TEST(TestFlow());
    /*RUN_TEST(TestRandom());)*/

    return 0;
}
/* params = 1 is for ascending, params = 0 is for descending */
int IsInDirection(const void *current, const void *data, const void *params)
{
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

int Multi(void *data, const void *args)
{
   *(int *)data *= *(int *)args;
   
   return 0;  
}

int TestCreate()
{
    int params = 1;
    int *params_ptr = &params;
    int flag = 0;
    bst_t *bst = BSTCreate(IsInDirection, (void *)params_ptr);
    int is_not_empty = BSTIsEmpty(bst);
    bst_it_t end = BSTEnd(bst);
    bst_it_t begin = BSTBegin(bst);
    
    if (0xDEADBEEF != (size_t)BSTGetData(begin))
    {
        flag = 1;
        printf("begin\n");
    }
    
    if (0xDEADBEEF != (size_t)BSTGetData(end))
    {
        flag = 1;
        printf("end\n");
    }
    
    if (!is_not_empty)
    {
        flag = 1;
        printf("is empty\n");
    }
    
    if (NULL == bst)
    {
        printf("create\n");
        flag = 1;
    }
    
    BSTDestroy(bst);
    
    printf ("functions on empty tree");
    
    return flag;
}

int TestFlow()
{
    int params = 1;
    int *params_ptr = &params;
    int flag = 0;
    bst_t *bst = BSTCreate(IsInDirection, (void *)params_ptr);
    int is_not_empty = 0;
    bst_it_t end = 0; 
    bst_it_t begin = 0;
    size_t size = 0;
    int first = 20;
    int second = 10;
    int third = 25;
    int firth = 30;
    int fifth = 15;
    int six = 70;
    int seventh = 5;
    int eight = 12;
    int nine = 18;
    int ten = 11;
    int eleven = 45;
    int *first_ptr = &first;
    int *second_ptr = &second;
    int *third_ptr = &third;
    int *firth_ptr = &firth;
    int *fifth_ptr = &fifth;
    int *six_ptr = &six;
    int *seven_ptr = &seventh;
    int *eight_ptr = &eight;
    int *nine_ptr = &nine;
    int *ten_ptr = &ten;
    int *eleven_ptr = &eleven;
    int status = 0;
    int args = 2;
    int *args_ptr = &args;
    bst_it_t runner = BSTBegin(bst);
    bst_it_t first_itr = BSTInsert(bst, first_ptr);
    bst_it_t second_itr = BSTInsert(bst, second_ptr);
    bst_it_t third_itr = BSTInsert(bst, third_ptr);
    bst_it_t firth_itr = BSTInsert(bst, firth_ptr);
    bst_it_t fifth_itr = BSTInsert(bst, fifth_ptr);
    bst_it_t six_itr = BSTInsert(bst, six_ptr);
    bst_it_t seven_itr = BSTInsert(bst, seven_ptr);
    bst_it_t eight_itr = BSTInsert(bst, eight_ptr);
    bst_it_t nine_itr = BSTInsert(bst, nine_ptr);
    bst_it_t ten_itr = BSTInsert(bst, ten_ptr);
    bst_it_t eleven_itr = BSTInsert(bst, eleven_ptr);
    
    bst_it_t next_of_10 = BSTNext(second_itr);
    bst_it_t next_of_5 = BSTNext(seven_itr);
    bst_it_t next_of_18 = BSTNext(nine_itr);
    bst_it_t next_of_70 = BSTNext(six_itr);
    
    bst_it_t prev_of_20 = BSTPrev(first_itr);
    bst_it_t prev_of_15 = BSTPrev(fifth_itr);
    bst_it_t prev_of_30 = BSTPrev(firth_itr);
    
    bst_it_t find_node = BSTFind(bst, fifth_ptr);
    
    is_not_empty = BSTIsEmpty(bst);
    end = BSTEnd(bst);
    begin = BSTBegin(bst);
    
    size = BSTCount(bst);
    if (11 != size)
    {
        flag = 1;
    }
  
    if (12 != *(int *)BSTGetData(BSTNext(ten_itr)))
    {
        flag = 1;
    }  
    
    if (30 != *(int *)BSTGetData(BSTNext(third_itr)))
    {
        flag = 1;
    }     
      
    if (11 != *(int *)BSTGetData(BSTPrev(eight_itr)))
    {
        flag = 1;
    }  
      
    if (30 != *(int *)BSTGetData(BSTPrev(eleven_itr)))
    {
        flag = 1;
    }    
    
    if (15 != *(int *)BSTGetData(find_node))
    {
        flag = 1;
    }
    
    if ((5 != *(int *)BSTGetData(begin)))
    {
        flag = 1;
    }
    
    if (0xDEADBEEF != (size_t)BSTGetData(end))
    {
        flag = 1;
        printf("end\n");
    }  
    
    if (!(20 == *(int *)BSTGetData(first_itr)))
    {
        flag = 1;
    }
    
    if (is_not_empty)
    {
        flag = 1;
        printf("is empty\n");
    }
    
    if ((11 != *(int *)BSTGetData(next_of_10)))
    {
        flag = 1;
    }

    if ((10 != *(int *)BSTGetData(next_of_5)))
    {
        flag = 1;
    }
    
    if ((20 != *(int *)BSTGetData(next_of_18)))
    {
        flag = 1;
    }
    
    if (0xDEADBEEF != (size_t)BSTGetData(next_of_70))
    {
        flag = 1;
        printf("end\n");
    }  

    if ((18 != *(int *)BSTGetData(prev_of_20)))
    {
        flag = 1;
    }

    if ((12 != *(int *)BSTGetData(prev_of_15)))
    {
        flag = 1;
    }
    
    if ((25 != *(int *)BSTGetData(prev_of_30)))
    {
        flag = 1;
    }
    
    BSTRemove(fifth_itr);
    if (10 != BSTCount(bst) && 12 != *(int *)BSTGetData(BSTPrev(fifth_itr)))
    {
        flag = 1;
    }
    
    status = BSTForEach(begin, end, Multi, args_ptr); 
    if (0 != status)
    {
        flag = 1;
    }
    
    BSTDestroy(bst);
    if (0 != BSTCount(bst))
    {
        flag = 1;
    }
    
    /*while (runner != BSTEnd(bst))
    {
        printf("%d\n", *(int *)BSTGetData(runner));
        runner = BSTNext(runner);
    }*/
    
    printf ("flow");
    
    return flag;
}

int TestRandom()
{
    int flag = 0;
    int params = 1;
    int *params_ptr = &params;
    bst_t *bst = BSTCreate(IsInDirection, (void *)params_ptr);
    int size = 100;
    int store_arr[100];
    int sorted_arr[100];
    int i = 0;
    int b = 0;
    bst_it_t runner = BSTBegin(bst);
       
    for (; i < size; ++i)
    {
        b = rand()%100;
        store_arr[i] = b;
        BSTInsert(bst, &store_arr[i]);
    }
    
    runner = BSTBegin(bst);
    i = 0;
    
    while (runner != BSTEnd(bst))
    {
        sorted_arr[i] = *(int *)BSTGetData(runner);
        runner = BSTNext(runner);
        ++i;
    }
    
    for (i = 0; i < size - 1; ++i)
    {
        if (sorted_arr[i] > sorted_arr[i + 1])
        {
            flag = 1;
            printf("not sorted\n");
        }
    }    
    
    printf("random numbers");
    
    return flag;
}
