#include <pthread.h>/* threads */
#include <stdlib.h>/* malloc */ 
#include <unistd.h> /* sleep */
#include <stdio.h>/* printf */
#include <omp.h>

size_t num = 800000000; 

int main()
{	
	size_t i = 0;
	int sum = 0;

    #pragma omp parallel for
	for(i = 1; i <= num; ++i) 
	{
		if((num % i) == 0)
		{
			sum += i;	
		}
	}

	printf("sum of dividers: %d", sum);

	return 0; 
}