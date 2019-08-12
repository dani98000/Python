#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *thread1_func(void *data)
{
	(void)data;
	int i = 2;
	int h;
	static int a = 5;
	int *arr = (int *)malloc(5 * sizeof(*arr));
	printf("Stack [Thread1]: %p\n", &i);
	printf("Data segment [Thread1]: %p\n", &a);	
	printf("BSS [Thread1]: %p\n", &h);
	printf("Heap [Thread1]: %p\n", &arr);	


	return NULL;
}

void *thread2_func(void *data)
{
	(void)data;
	int i = 3;
	int h;
	static int a = 5;
	int *arr = (int *)malloc(5 * sizeof(*arr));
	printf("Stack [Thread2]: %p\n", &i);
	printf("Data segment [Thread2]: %p\n", &a);
	printf("BSS [Thread2]: %p\n", &h);	
	printf("Heap [Thread1]: %p\n", &arr);	


	return NULL;
}

int main()
{
	int ret = 0;
	int i = 0;
	pthread_t thread1_id;
	pthread_t thread2_id;

	ret = pthread_create(&thread1_id, NULL, thread1_func, NULL);
	if(ret != 0) 
	{
		perror("error: \n");
	}

	ret = pthread_create(&thread2_id, NULL, thread2_func, NULL);
	if(ret != 0) 
	{
		perror("error: \n");
	}


	ret = pthread_join(thread1_id, NULL);
	if(ret != 0) 
	{
		perror("error: \n");
	}

	ret = pthread_join(thread2_id, NULL);
	if(ret != 0) 
	{
		perror("error: \n");
	}

  	return 0;
}