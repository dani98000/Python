/*******************************************************************************
* Programmer: Eldad Carin
* Reviewer: 
* File: scheduler code
* Date: 13-06-2019 16:20:04
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <unistd.h> /* sleep */
#include <time.h>   /*time*/
#include <errno.h> /* ENOMEM */

#include "../include/Scheduler/scheduler.h"  /* scheduler header */
#include "../include/Scheduler/task.h"       /* task header */
#include "../include/PQ/pq.h" /* Priority Queue header */

static int ScdInfrastructure(scd_t *scheduler);

struct scheduler
{
	pq_t *task_list;
	int should_stop;	
};

static int IsBefore(const void *listed, const void *new, const void *params)   
{
    (void)params;
    
    return TaskGetTime((task_t *)new) < TaskGetTime((task_t *)listed);
}

static int IsMatch(const void *data, const void *param, const void *moredata)      
{
    unid_t data_uid = TaskGetUID((task_t *)data);
    unid_t param_uid = *(unid_t *)param;
    
    assert(data);
    assert(param);
    
    (void)moredata;
    
    if (UIDIsSame(data_uid, param_uid))
    {
        TaskDestroy((void *)data);
        
        return 0;    
    }
       
    return 1;
}

scd_t *ScdCreate()
{
    scd_t *new_scheduler = (scd_t *)malloc(sizeof(scd_t));
    if (NULL == new_scheduler)
    {
        return NULL;
    }
    
    new_scheduler->should_stop = 0;
    
    new_scheduler->task_list = PQCreate((pqcmp_f)IsBefore);
    if (NULL == new_scheduler->task_list)
    {
        free(new_scheduler);
        
        return NULL;
    }
    
    return new_scheduler;
}

void ScdDestroy(scd_t *scheduler)
{
    task_t *task = NULL;
    
    assert (NULL != scheduler);
    
    while (!ScdIsEmpty(scheduler))
    {
        task = PQPeek(scheduler->task_list);
        PQDequeue(scheduler->task_list);
        TaskDestroy(task);
    }
    
    PQDestroy(scheduler->task_list);
    free(scheduler);
}

unid_t ScdAdd(scd_t *scheduler, time_t interval, func_t func, void *params)
{
    task_t *new_task = NULL;
    
    assert (NULL != scheduler && NULL != func);
    
    new_task = TaskCreate(interval, func, params);
    if (NULL == new_task)
    {
        return bad_uid;
    }
    
    PQEnqueue(scheduler->task_list, (void *)new_task);
    
    return TaskGetUID(new_task);
}                                           

int ScdRemove(scd_t *scheduler, unid_t task_uid) 
{    
    assert (NULL != scheduler);    
    
    if (1 == PQErase(scheduler->task_list, &task_uid, IsMatch))
    {
        return 1;
    }
    
    return 0;
}

size_t ScdRun(scd_t *scheduler) /* returns number of remaining tasks in the queue */
{  
    assert (NULL != scheduler);
    
    scheduler->should_stop = 0;
    
    while (1 != scheduler->should_stop && !ScdIsEmpty(scheduler))
    {        
        if (ENOMEM == errno)
        {
            return ScdSize(scheduler);
        }
        
        ScdInfrastructure(scheduler); 
    }
    
    return ScdSize(scheduler);
}

void ScdStop(scd_t *scheduler)
{
    assert (NULL != scheduler);
    
    scheduler->should_stop = 1;
}

size_t ScdSize(const scd_t *scheduler)
{
    assert (NULL != scheduler);
    
    return PQSize(scheduler->task_list);
}

int ScdIsEmpty(const scd_t *scheduler)
{
    assert (NULL != scheduler);
    
    return PQIsEmpty(scheduler->task_list);
}

static int ScdInfrastructure(scd_t *scheduler)
{
    int execute_ret = 0;
    task_t *task = NULL;
    time_t task_run_time = 0;
    time_t sleep_ret = 0;
    
    assert(NULL != scheduler);
    
    task = PQPeek(scheduler->task_list);

    task_run_time = TaskGetTime(task);
    
    if (time(NULL) < task_run_time)
    {
        sleep_ret = sleep(task_run_time - time(NULL));
        if (0 < sleep_ret)
        {
            sleep(sleep_ret);
        }        
    }

    execute_ret = TaskExecute(task);
    if (1 == execute_ret)
    {
       if (1 == PQEnqueue(scheduler->task_list, (void *)task))
       {
           errno = ENOMEM;
        
           return 1;
       }
    }
    else
    {
        TaskDestroy(task);
    }

    PQDequeue(scheduler->task_list);     
    
    return 0;
}
