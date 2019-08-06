
int SumOfTwo(unsigned int *arr, int *val1, int *val2, int arr_length, int sum_of_two)
{
	int i = 0, j = 0;
	int temp = 0;

	for (i = 0; i < arr_length; ++i)
	{
		for (j = 0; j < arr_length; ++j)
		{
			if(i == j)
			{
				++j;
			}
			if(arr[i] + arr[j] == sum_of_two)
			{
				*val1 = arr[i];
				*val2 = arr[j];
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	unsigned int arr[] = {5,1,0,3,4,7,8,5,2,1,1,0};
	int val1 = 0, val2 = 0;
	int arr_length = sizeof(arr) / sizeof(int);
	SumOfTwo(arr, &val1, &val2, arr_length, 13);
	printf("val1: %d, val2: %d", val1, val2);

	return 0;
}