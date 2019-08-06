#include <pthread.h>/* threads */
#include <stdlib.h>/* malloc */ 
#include <unistd.h> /* sleep */
#include <stdio.h>/* printf */

size_t num = 800000000; 

struct div
{
	size_t from;
	size_t to;
	size_t sum;
};

void *SumOfDiv(void *div)
{
	struct div *my_data;   
    size_t i = 1; 
    my_data = (struct div *)div;
    
    for(i = my_data->from + 1; i <= my_data->to; ++i)
	{
		if((num % i) == 0)
		{
			my_data->sum += i;
		}
	} 

	return NULL;
}

int main(int args, char**argv)
{	
	int num_of_threads = atoi(argv[1]);
	pthread_t thr;
	size_t i = 0;
	struct div *div = malloc(num_of_threads * sizeof(*div));
	int ret = 0, res = 0;
	void *status = NULL;
	int div_sum = 0;
	div->sum = 0;

	for(i = 0; i < num_of_threads; ++i) 
	{
		div[i].from = i*(num/num_of_threads);
		if(i == num_of_threads - 1)
		{
			div[i].to = num;	
		}
		else
		{
			div[i].to = div[i].from + num/num_of_threads;
		}
		ret = pthread_create(&thr, NULL, SumOfDiv, div+i);
	}

	for(i = 0; i < num_of_threads; ++i) 
	{
		pthread_join(thr, &status);
	}


	for(i = 0; i < num_of_threads; ++i)
	{
		div_sum += div[i].sum;
	}

	printf("sum of dividers: %d", div_sum);

	free(div);

	return 0; 
}