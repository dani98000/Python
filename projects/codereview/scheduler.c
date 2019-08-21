#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <time.h>   /* time   */
#include <unistd.h> /* sleep  */
#include <errno.h>  /* errno  */

#include "scheduler.h" /* Scheduler header file*/
#include "task.h" /* Task header file*/
#include "pq.h"

#define UNUSED(X) (void)(X)

static int IsBefore(const void *data, const void *key, const void *params);
static int CompareUID(const void *data, const void *key, const void *params);

struct scheduler
{
	pq_t *task_list;
	int should_stop;	
};

scd_t *ScdCreate()
{
	scd_t *scd = (scd_t *)malloc(sizeof(scd_t));
	if(NULL == scd)
	{		
		return NULL;
	}
	
	scd->task_list = PQCreate(IsBefore);
	if(NULL == scd->task_list)
	{
		free(scd);
		
		return NULL;
	}
	
	scd->should_stop = 0;
	
	return scd;
}

void ScdDestroy(scd_t *scheduler)
{
	assert(NULL != scheduler);
	
	while(!ScdIsEmpty(scheduler))
	{
		TaskDestroy(PQPeek(scheduler->task_list));
		PQDequeue(scheduler->task_list);
	}
	
	PQDestroy(scheduler->task_list);
	free(scheduler);
}

unid_t ScdAdd(scd_t *scheduler, time_t interval, func_t func, void *params)
{
	task_t *task = NULL;

	assert(NULL != scheduler);	
	assert(NULL != func);	
	
	task = TaskCreate(interval, func, params);
	if(NULL == task)
	{
		return bad_uid;
	}
	
	if(PQEnqueue(scheduler->task_list, task))
	{
		return bad_uid;
	}
	
	return TaskGetUID(task);
}

int ScdRemove(scd_t *scheduler, unid_t task_uid) 
{
	assert(NULL != scheduler);

	return(PQErase(scheduler->task_list, &task_uid, CompareUID));
}

size_t ScdRun(scd_t *scheduler) 
{
	task_t *task = NULL;
	time_t time_left = 0;
	time_t sleep_left = 0;
	
	assert(NULL != scheduler);
		
	scheduler->should_stop = 0;
	
	while(!ScdIsEmpty(scheduler) && 0 == scheduler->should_stop)
	{
		task = PQPeek(scheduler->task_list);
		time_left = TaskGetTime(task) - time(NULL); 
		
		if(time_left > 0)
		{
			sleep_left = sleep(time_left);
			while(sleep_left > 0)
			{
				sleep_left = sleep(sleep_left);
			}
		}

		if(TaskExecute(task) == 1)
		{
			if(!PQEnqueue(scheduler->task_list, task))
			{
				PQDequeue(scheduler->task_list);
			}
			else
			{
				errno = ENOMEM;
				ScdStop(scheduler);
			}
		}
		else
		{
			PQDequeue(scheduler->task_list);
			TaskDestroy(task);
		}
	}
	
	return (ScdSize(scheduler));
}

void ScdStop(scd_t *scheduler)
{
	assert(NULL != scheduler);

	scheduler->should_stop = 1;
}

size_t ScdSize(const scd_t *scheduler)
{
	assert(NULL != scheduler);

	return PQSize(scheduler->task_list);
}

int ScdIsEmpty(const scd_t *scheduler)
{
	assert(NULL != scheduler);

	return PQIsEmpty(scheduler->task_list);
}

static int IsBefore(const void *data, const void *key, const void *params)
{
	UNUSED(params);

	return(((time_t *)TaskGetTime(data)) > ((time_t *)TaskGetTime(key))); 
}

static int CompareUID(const void *data, const void *key, const void *params)
{
	UNUSED(params);

	if(UIDIsSame(TaskGetUID(data), *((unid_t *)key)))
	{
		TaskDestroy((task_t *)data);
		
		return 1;
	}
	
	return 0;
}
