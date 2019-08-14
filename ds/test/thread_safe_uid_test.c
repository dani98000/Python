#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 30000

int g_flag = 0;

void *thr_func(void *args)
{
	while(!g_flag)
		;

	unid_t *uid = (unid_t *)args;
	*uid = UIDCreate();

	return NULL;
}

int main()
{
	pthread_t thr;
	int ret = 0;
	int i = 0;
	int j = 0;
	int res = 0;
	pthread_t *thr_id = (pthread_t *)malloc(sizeof(pthread_t) * NUM_THREADS);
	unid_t *uid = (unid_t *)malloc(NUM_THREADS * sizeof(*uid));

	for(i = 0; i < NUM_THREADS; ++i)
	{
		ret = pthread_create(&thr_id[i], NULL, thr_func, &uid[i]);
		if(ret != 0) 
		{
			perror("error: \n");
	    }
	}
	g_flag = 1;

    for(i = 0; i < NUM_THREADS; ++i)
	{
		ret = pthread_join(thr_id[i], NULL);
		if(ret != 0) 
		{
			perror("error: \n");
	    }
	}

	for(i = 0; i < NUM_THREADS - 1; ++i)
	{
		for(j = i + 1; j < NUM_THREADS; ++j)
		if(UIDIsSame(uid[i], uid[j]))
		{
			++res;
			printf("index of failure: i:%d, j:%d", i,j);
		}

	}

	printf("result: %d\n", res);

  	return 0;
}
