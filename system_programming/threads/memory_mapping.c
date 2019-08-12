int i;

int main()
{
	static int x;
	static int y = 5;
	int a = 5;
	printf("BSS: %p\n", &i);
	printf("BSS: %p\n", &x);
	printf("Data segment: %p\n", &y);
	printf("Stack: %p\n", &a);

	return 0;
}

void *thread1_func(void *data)
{
	(void)data;
	

	return NULL;
}

void *thread1_func(void *data)
{
	(void)data;


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


	ret = pthread_join(&thread1_id, NULL);
	if(ret != 0) 
	{
		perror("error: \n");
	}

	ret = pthread_join(&thread1_id, NULL);
	if(ret != 0) 
	{
		perror("error: \n");
	}

  	return 0;
}