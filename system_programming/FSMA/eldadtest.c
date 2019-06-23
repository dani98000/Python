/*******************************************************************************
* Programmer: Eldad Carin
* Reviewer: 
* File: fsma testing
* Date: 19-06-2019 13:29:42
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> 	/* printf */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <string.h> /* string functions */

#include "fsma.h"
/*Print Colors*****************************************************************/
#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#define RUN_TEST(test_name) \
{ \
if (0 == test_name()) \
{ puts(GREEN"SUCCESS"RESET); } \
else \
{ puts(RED"FAILURE"RESET); } \
}

/*Globals**********************************************************************/
int i; 
int j; 

/*Functions definitions********************************************************/
static int TestFSMASuggestSize();
static int TestInit();
static int TestAllocFreeCount();

/*Main*************************************************************************/
int main(void)
{
    puts(CYAN"\n         FSMA:"RESET);
    puts(CYAN"----------------------------"RESET);
    
	RUN_TEST(TestFSMASuggestSize);
	RUN_TEST(TestInit);	
	RUN_TEST(TestAllocFreeCount);		
	

    puts(CYAN"----------------------------"RESET);       
    puts(MAGENTA"----------------------------"RESET);  

    return EXIT_SUCCESS;
}
/******************************************************************************/
static int TestFSMASuggestSize()
{
    size_t block_size = 8;
    size_t n_blocks = 10;
    
    ++i;
    if (184 != FSMASuggestSize(n_blocks, block_size))
    {
        printf(RED"%d. FSMASuggestSize\n"RESET, i);
        
        return 1;    
    }
    printf(GREEN"%d. FSMASuggestSize\n"RESET, i);


    return 0;
}
/******************************************************************************/
static int TestInit()
{
    size_t block_size = 8;
    size_t n_blocks = 10;    
    size_t pool_size = 0;
    char *pool = NULL;
    fsma_t *fsma = NULL;
    
    pool_size = FSMASuggestSize(n_blocks, block_size);
    
    ++i;
    pool = malloc(pool_size);
    if (NULL == pool)
    {
        printf(RED"%d. TestInit malloc failure\n"RESET, i);
        
        return 1;       
    }
    
    fsma = FSMAInit(pool, pool_size, block_size);
    if (NULL == fsma)
    {
        printf(RED"%d. Init\n"RESET, i);
        
        return 1;        
    }
    printf(GREEN"%d. Init\n"RESET, i);
    printf(GREEN"Size of pool is %lu\n"RESET, pool_size);
    
    free(pool);

    return 0;
}
/************************************/
static int TestAllocFreeCount()
{
    size_t block_size = 1000;
    size_t n_blocks = 4;    
    size_t pool_size = 0;
    char *pool = NULL;
    fsma_t *fsma = NULL;
    char *first = NULL;
    char *second = NULL;    
    char *third = NULL;
    char *fourth = NULL;
    char *fifth = NULL;       
    pool_size = FSMASuggestSize(n_blocks, block_size);
    
    ++i;
    pool = malloc(pool_size);
    if (NULL == pool)
    {
        printf(RED"%d. TestAllocFreeCount malloc failure\n"RESET, i);
        
        return 1;        
    }
    
    fsma = FSMAInit(pool, pool_size, block_size);
    if (NULL == fsma)
    {
        printf(RED"%d. Init of AllocFreeCount\n"RESET, i);
        
        return 1;        
    }
    
    printf(GREEN"%d. Init of AllocFreeCount\n"RESET, i);
    printf(GREEN"Size of pool is %lu\n"RESET, pool_size);
++i;    
    if (4 != FSMACountFree(fsma))
    {
    	printf("%lu",FSMACountFree(fsma));
        printf(RED"%d. Count to 4\n"RESET, i);
        
        return 1;           
    }
#if 0    
    printf(GREEN"%d. Count to 4\n"RESET, i);        

     
    first = FSMAAlloc(fsma);
    ++j;
    printf("%d test %p\n", j, first); 
++i;
    if (3 != FSMACountFree(fsma))
    {
        printf(RED"%d. Count to3\n"RESET, i);
        
        return 1;           
    }
    printf(GREEN"%d. Count to 3\n"RESET, i);  
    
    
    second = FSMAAlloc(fsma);
    ++j;
    printf("%d test %p\n", j, second);    
    third = FSMAAlloc(fsma);    
    ++j;
    printf("%d test %p\n", j, third);    
    fourth = FSMAAlloc(fsma);
    ++j;
    printf("%d test %p\n", j, fourth);
++i;
    if (0 != FSMACountFree(fsma))
    {
        printf(RED"%d. Count to 0\n"RESET, i);
        
        return 1;           
    }
    printf(GREEN"%d. Count to 0\n"RESET, i);              
   
    fifth = FSMAAlloc(fsma);
    ++j;
    printf("%d test %p\n", j, fifth);    
    
    FSMAFree(first); 
++i;
    if (1 != FSMACountFree(fsma))
    {
        printf(RED"%d. Count to 1 after free\n"RESET, i);
        
        return 1;           
    }
    printf(GREEN"%d. Count to 1 after free\n"RESET, i); 

    FSMAFree(second);
    FSMAFree(third);        
    FSMAFree(fourth);  
++i;
    if (4 != FSMACountFree(fsma))
    {
        printf(RED"%d. Count to 4 after free\n"RESET, i);
        
        return 1;           
    }
    printf(GREEN"%d. Count to 4 after free\n"RESET, i);    
#endif
    free(pool);
    return 0;
}


