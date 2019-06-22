/*******************************************************************************
* Programmer: Eldad Carin
* Reviewer: 
* File: scheduler testing
* Date: 13-06-2019 16:20:04
*******************************************************************************/

#include <assert.h> /* assert */
#include <stdio.h> 	/* printf */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <string.h> /* string functions */
#include <time.h>   /* time */

#include "./include/scheduler.h"
#include "./include/pq.h" /* Priority Queue header */
/*Print Colors*****************************************************************/
#define BLUE      "\x1b[34m"
#define RED       "\x1b[31m"
#define REDL      "\x1b[91m"
#define YELLOW    "\x1b[1;33m" 
#define YELLOW2   "\x1b[33m"   
#define CYANDARK  "\x1b[36m"
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define GREENL    "\x1b[92m"
#define MAGENTA   "\x1B[35m"
#define ORANGE    "\x1b[33m"
#define BLINKON   "\x1b[5m"
#define BLINKOFF  "\x1b[25m"
#define BOLDON    "\x1b[1m"
#define BOLDOFF   "\x1b[21m"
#define UNDERLON  "\x1b[4m"
#define UNDERLOFF "\x1b[24m"
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
size_t i; 

static long PrintCurrentTime(void *params)
{	
	time_t now = time(NULL);
	
	printf(ORANGE UNDERLON"%s"UNDERLOFF RESET, ctime(&now));
	
	(void)params;
	return (long)params;
}

static long PrintCurrentTime2(void *params)
{	
	time_t now = time(NULL);
	
	printf(GREEN"%s"RESET, ctime(&now));
	
	return (long)params;
}

static long PrintCurrentTime3(void *params)
{	
	time_t now = time(NULL);
	
	printf(CYAN"%s"RESET, ctime(&now));
	
	return (long)params;
}

static long PrintCurrentTime4(void *params)
{	
	time_t now = time(NULL);
	
	printf(YELLOW"%s"RESET, ctime(&now));
	
	return (long)params;
}

static long Stop(void *params) 
{
    assert(params);
         
    ScdStop((scd_t *)params);
    
    return -1;
}

/*Functions definitions********************************************************/
static int TestCreate();

/*Main*************************************************************************/
int main(void)
{
    puts(MAGENTA"----------------------------"RESET);  
    puts(CYAN"      Scheduler:"RESET);
    puts(CYAN"----------------------------"RESET);
    
	RUN_TEST(TestCreate);

    puts(CYAN"----------------------------"RESET);       
    puts(MAGENTA"----------------------------"RESET);  

    return EXIT_SUCCESS;
}
/******************************************************************************/
static int TestCreate()
{
    unid_t uid1 = bad_uid;
    unid_t uid2 = bad_uid;
    unid_t uid3 = bad_uid;
    unid_t uid4 = bad_uid;    
    unid_t uidstop = bad_uid;
    scd_t *scheduler = ScdCreate();
    
    ++i;
    if (NULL == scheduler)
    {
        printf(RED"%lu. Create"RESET, i);
        puts("");
        return 1;
    }   
    printf(GREEN"%lu. Create\n"RESET, i);
    
    ++i;
    if (0 != ScdSize(scheduler))
    {
        printf(RED"%lu. Size at empty"RESET, i);
        puts("");
        return 1;
    }   
    printf(GREEN"%lu. Size at empty\n"RESET, i);

    ++i;
    if (!ScdIsEmpty(scheduler))
    {
        printf(RED"%lu. IsEmpty at empty"RESET, i);
        puts("");
        return 1;
    }   
    printf(GREEN"%lu. IsEmpty at empty\n"RESET, i);

    ++i;
    
    uid1 = ScdAdd(scheduler, 2, PrintCurrentTime, 0);   /*add */
    if (UIDIsSame(uid1, bad_uid))
    {
        printf(RED"%lu. Add"RESET, i);
        puts("");
        return 1;
    }
    printf(GREEN"%lu. Add\n"RESET, i);
    
    ++i;
    if (1 != ScdSize(scheduler))
    {
        printf(RED"%lu. Size at 1"RESET, i);
        puts("");
        return 1;
    }   
    printf(GREEN"%lu. Size at 1\n"RESET, i);

    ++i;
    if (ScdIsEmpty(scheduler))
    {
        printf(RED"%lu. IsEmpty at 1"RESET, i);
        puts("");
        return 1;
    }   
    printf(GREEN"%lu. IsEmpty at 1\n"RESET, i);
    
    uid3 = ScdAdd(scheduler, 1, PrintCurrentTime3, (void *)-1); 
    uid2 = ScdAdd(scheduler, 3, PrintCurrentTime2, (void *)-1);   /*add */
  
    uid3 = ScdAdd(scheduler, 21, PrintCurrentTime3, (void *)1); 
    uid4 = ScdAdd(scheduler, 15, PrintCurrentTime4, (void *)1); 
    uidstop = ScdAdd(scheduler, 4, Stop, scheduler);
    uidstop = ScdAdd(scheduler, 25, Stop, scheduler);
  
  
    uid2 = ScdAdd(scheduler, 28, PrintCurrentTime2, (void *)10);   /*add */

    ScdRun(scheduler);              /* run */

    ScdRun(scheduler);              /* run */  
    
    ScdRun(scheduler);              /* run */  
    
    ScdDestroy(scheduler);
    
    return 0;
}







