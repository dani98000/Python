#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../../include/Scheduler/task.h"

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
	task_t *task = (task_t *)malloc(sizeof(task_t));
	if(NULL == task)
	{
		free(task);
		
		return NULL;
	}
	
	task->func = func;
	task->params = params;
	task->uid = UIDCreate();
	task->interval = interval;
	task->time_to_run = time(NULL) + interval;
	
	return task;
}

void TaskDestroy(task_t *task)
{
	free(task);
}

int TaskExecute(task_t *task)
{
	int result = task->func(task->params);
	time_t time_left = TaskGetTime(task) - time(NULL); 
	
	
	if(time_left <= 0)
	{
		task->time_to_run = time(NULL) + task->interval;
			
		if(result < 0)
		{		
			return 0;
		}
		
		if(result > 0)
		{
			task->interval = result;
		}
	}
	
	task->time_to_run = time(NULL) + task->interval;
	
	return 1;	
}

time_t TaskGetTime(const task_t *task)
{
	return task->time_to_run;
}

unid_t TaskGetUID(const task_t *task)
{
	return task->uid;
}
