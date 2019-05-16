#include <stdio.h>


int pow2(unsigned int x, int y)
{
	int res = x<<y;
	return res;
}

int IsPow2L(unsigned int n)
{
	unsigned int count = 0, temp = n;
	while((temp >= 1 ) && (count <= 1) )
	{
		if((temp & 1) == 1)
		{
			++count;
		}
		temp = temp>>1;
	}
	if(count == 1 && n > 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int Plusone(unsigned int n)
{
	if((n&1) == 1)
	{
		n = -(~n);	
	}
	else
	{
		n = n | (1 << 0);
	}
	

	printf("%d\n", n);
	
	return n;
}

int IsPow2(unsigned int n)
{
	if (!(n & (n - 1)) && n > 1)
	{
		return 1;
	} 
	
	return 0;
}

unsigned int CountSet(unsigned int arr[], int arr_length)
{
	int i, temp, count = 0;
	for(i = 0; i < arr_length; i++)
	{
		temp=arr[i];
		while(temp >= 1 ) 
		{	
			if((temp & 1) == 1)
			{
				++count;
			}
			temp = temp>>1;
		}
		if(count == 3)
		{
			printf("%d\n", arr[i]);
		}
		count = 0;
	}
	return 0;
}
	
	
void byte_mirror(unsigned int *n)
{
	int i;
	for (i = 0 ; i != 8 ; i++) 
	{
    	if (*n & (1 << i)) 
    	{
            *n = *n | (0 << i);                
    	} 
    	else 
    	{
			*n = *n | (1 << i);              
    	}
	}	
	printf("%d\n",*n);
}

	

int main()
{
	unsigned int a[] = {8, 5, 10, 12, 7, 14};
	unsigned int b=1;
	printf("%d\n", pow2(5, 2));
	printf("%d\n", IsPow2(2));
	printf("%d\n", IsPow2L(2));
	Plusone(30);
	CountSet(a, 6);
	byte_mirror(&b);
	return 0;
}


