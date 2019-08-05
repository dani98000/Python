#include <pthread.h>/* threads */
#include <stdlib.h>/* malloc */ 
#include <unistd.h> /* sleep */
#include <stdio.h>/* printf */

#define NUM_THREADS 4
size_t num = 5000; 

struct args
{
	size_t from;
	size_t to;
	size_t sum;
};

void *SumOfDiv(void *args)
{
	struct args *my_data;   
    size_t i = 1; 
    my_data = (struct args *)args;
    
    for(i = my_data->from + 1; i <= my_data->to; ++i)
	{
		if((num % i) == 0)
		{
			my_data->sum += i;
		}
	} 

	return NULL;
}

int main()
{
	pthread_t thr;
	size_t i = 0;
	struct args *args = malloc(NUM_THREADS * sizeof(*args));
	int ret = 0, res = 0;
	void *status = NULL;
	int div_sum = 0;
	args->sum = 0;

	for(i = 0; i <= NUM_THREADS; ++i) 
	{
		args[i].from = i*(num/NUM_THREADS);
		args[i].to = args[i].from + num/NUM_THREADS;
		ret = pthread_create(&thr, NULL, SumOfDiv, args+i);
	}

	for(i = 0; i <= NUM_THREADS; ++i) 
	{
		pthread_join(thr, &status);
	}


	for(i = 0; i < NUM_THREADS; ++i)
	{
		div_sum += args[i].sum;
	}

	printf("sum of dividers: %ld", div_sum);

	free(args);

	return 0; 
}