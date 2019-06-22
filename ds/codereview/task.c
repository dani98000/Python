/*******************************************************************************
* Programmer: Eldad Carin
* Reviewer: 
* File: task code
* Date: 13-06-2019 16:24:08
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /*  malloc */
#include <time.h> /* time funcs */

#include "../include/Scheduler/task.h"

struct task
{
	func_t func;
	void *params;
	unid_t uid;
	size_t interval;
	time_t time_to_run;	
};

task_t *TaskCreate(size_t interval, func_t func, void *params)
{
    task_t *new_task = NULL;
    
    assert(NULL != func);
    
    new_task = (task_t *)malloc(sizeof(task_t));
    if (NULL == new_task)
    {
        return NULL;
    }   
    
    new_task->func = func;
    new_task->params = params;
    
    new_task->uid =  UIDCreate();
    if (UIDIsBad(TaskGetUID(new_task)))
    {
        free(new_task);
        return NULL;
    }     
    
    new_task->interval = interval;
    new_task->time_to_run =  time(NULL) + interval;
    
    return new_task;
}

void TaskDestroy(task_t *task)
{  
    free(task);    
}
   
int TaskExecute(task_t *task)
{
    int func_ret = 0;
    assert(NULL != task);
    
    if (task->time_to_run < time(NULL))
    {
        task->time_to_run = time(NULL) + task->interval;
        
        return 1;
    }
    
    func_ret = task->func(task->params);
    
    if (0 <= func_ret)
    {     
        if (0 < func_ret)
        {
            task->interval = func_ret;
        }
        
        task->time_to_run =  time(NULL) + task->interval;
        
        return 1;
    }
    
    return 0;
}
    
time_t TaskGetTime(const task_t *task)
{
    assert(NULL != task);
    
    return task->time_to_run;    
}

unid_t TaskGetUID(const task_t *task)
{
    assert(NULL != task);
    
    return task->uid;    
}
