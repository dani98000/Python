#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>

#include "../../include/Scheduler/scheduler.h"
#include "../../include/PQ/pq.h"

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
	task_t *task = TaskCreate(interval, func, params);
	if(NULL == task)
	{
		return bad_uid;
	}
	
	PQEnqueue(scheduler->task_list, task);
	
	return TaskGetUID(task);
}

int ScdRemove(scd_t *scheduler, unid_t task_uid) /* returns 0 on success or 1 on failure (uid not found)*/ 
{
	task_t *task = NULL;
	pq_t *new_list = NULL;
	int flag = 0;
	
	assert(NULL != scheduler);
	
	new_list = PQCreate(IsBefore);
	if(NULL == new_list)
	{
		return 1;
	}
	
	while(!ScdIsEmpty(scheduler))
	{
		task = PQPeek(scheduler->task_list);
		PQDequeue(scheduler->task_list);
		
		if(UIDIsSame(TaskGetUID(task), task_uid))
		{
			TaskDestroy(task);
			flag = 0;
			continue;
		}
		
		PQEnqueue(new_list, task);
	}
	
	PQDestroy(scheduler->task_list);
	scheduler->task_list = new_list;
	return flag;
}

size_t ScdRun(scd_t *scheduler) 
{
	task_t *task = NULL;
	time_t time_left = 0;
	scheduler->should_stop = 0;	
	
	while(!ScdIsEmpty(scheduler) && scheduler->should_stop == 0)
	{
		task = PQPeek(scheduler->task_list);
		time_left = TaskGetTime(task) - time(NULL); 
		if(time_left > 0)
		{
			sleep(time_left);
		}

		if(TaskExecute(task) == 1)
		{
			PQDequeue(scheduler->task_list);
			PQEnqueue(scheduler->task_list, task);
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
	return(((time_t *)TaskGetTime(data)) > ((time_t *)TaskGetTime(key))); 
}

static int CompareUID(const void *data, const void *key, const void *params)
{
	return(UIDIsSame(TaskGetUID(data), *((unid_t *)key)));	
}
