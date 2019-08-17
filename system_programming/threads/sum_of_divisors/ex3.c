#include <pthread.h>/* threads */
#include <stdlib.h>/* malloc */ 
#include <unistd.h> /* sleep */
#include <stdio.h>/* printf */
#include <omp.h>/* openMP */

const int NUM = 800000000;

int main()
{	
	int i = 0;
	int sum = 0;

    #pragma omp parallel for reduction(+:sum)
	for(i = 1; i <= NUM; ++i) 
	{
		if((NUM % i) == 0)
		{
			sum += i;	
		}
	}

	printf("sum of dividers: %d", sum);

	return 0; 
}