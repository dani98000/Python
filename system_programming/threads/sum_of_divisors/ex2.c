#include <pthread.h>/* threads */
#include <stdlib.h>/* malloc */ 
#include <unistd.h> /* sleep */
#include <stdio.h>/* printf */

int num = 800000000; 

struct div
{
	int from;
	int to;
};

void *SumOfDiv(void *div)
{
	struct div *my_data;   
    int i = 1; 
    int sum = 0;
    my_data = (struct div *)div;
    
    for(i = my_data->from + 1; i <= my_data->to; ++i)
	{
		if((num % i) == 0)
		{
			sum += i;
		}
	} 

	return (void *)sum;
}

int main(int args, char**argv)
{	
	int num_of_threads = atoi(argv[1]);
	pthread_t thr;
	int i = 0;
	struct div *div = malloc(num_of_threads * sizeof(*div));
	pthread_t *id = (pthread_t *)malloc(sizeof(pthread_t) * num_of_threads);
	int ret = 0, res = 0;
	int div_sum = 0;
	size_t current_sum = 0;

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
		ret = pthread_create(&id[i], NULL, SumOfDiv, div+i);
	}

	for(i = 0; i < num_of_threads; ++i) 
	{
		pthread_join(id[i], (void *)&current_sum);
		div_sum += current_sum;	
	}

	printf("sum of dividers: %d", div_sum);

	free(div);

	return 0; 
}