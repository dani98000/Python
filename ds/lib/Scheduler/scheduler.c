#include <stdlib.h>
#include <stdio.h>


#include "../../include/Scheduler/task.h"
#include "../../include/PQ/pq.h"

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
		free(scd);
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
	PQDestroy(scheduler->task_list);
	free(scheduler);
}

unid_t ScdAdd(scd_t *scheduler, time_t interval, func_t func, void *params)
{
	task_t *task = TaskCreate(interval, func, params);
	if(NULL == task)
	{
		return bad_uid;
	}
	
	PQEnqueue(scheduler->task_list, func);
	
	return TaskGetUID(task);
}

int ScdRemove(scd_t *scheduler, unid_t task_uid) /* returns 0 on success or 1 on failure (uid not found)*/ 
{
	return(PQErase(scheduler->task_list, task_uid, CompareUID));
}

size_t ScdRun(scd_t *scheduler); /* returns number of remaining tasks in the queue */

void ScdStop(scd_t *scheduler)
{
	scheduler->should_stop = 1;
}

size_t ScdSize(const scd_t *scheduler)
{
	return PQSize(scheduler->task_list);
}

int ScdIsEmpty(const scd_t *scheduler)
{
	return PQIsEmpty(scheduler->task_list);
}

static int IsBefore(const void *data, const void *key, const void *params)
{
	return(*((time_t *)TaskGetTime(data)) > *((time_t *)TaskGetTime(key))) 
}

static int CompareUID(const void *data, const void *key, const void *params)
{
	return(UIDIsSame(TaskGetUID(data), key));	
}
