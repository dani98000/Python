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

unsigned int ThreeSet(unsigned int arr[], int arr_length)
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

int Div16(unsigned int a)
{
	if(a % 16 != 0)
	{

		a = a & 0xF0;
	}
	return a;
}

unsigned int CountSet(unsigned int num)
{
	int count = 0;
	while(num >= 1) 
	{	
		if((num & 1) == 1)
		{
			++count;
		}
		num = num>>1;
	}
	return count;
}

int TwoAndSix(unsigned char a)
{
	return((a & 0x22) == 0x22);
}

int TwoOrSix(unsigned char a)
{
	return(((a & 0x02) == 0x02) || ((a & 0x20) == 0x20));
}

void swap(unsigned int x,unsigned int y)
{
	x = x ^ y; 
    y = x ^ y; 
    x = x ^ y;
    printf("x = %d\ny = %d\n",x,y);
}

int SwapBits(unsigned int num) 
{ 
    unsigned int bit1 =  (num >> 2) & 1; 
    unsigned int bit2 =  (num >> 4) & 1; 
    unsigned int x = (bit1 ^ bit2); 
    unsigned int result;
    /* Put the xor bit back to their original positions */
    x = (x << 2) | (x << 4); 
	result = num ^ x; 
    return result;
} 

int main()
{
	unsigned int a[] = {8, 5, 10, 12, 7, 14};
	printf("%d\n", pow2(5, 2));
	printf("%d\n", IsPow2(2));
	printf("%d\n", IsPow2L(2));
	Plusone(30);
	ThreeSet(a, 6);
	printf("%d\n",Div16(49));
	printf("%d\n",CountSet(32));
	printf("%d\n",TwoAndSix(32));
	printf("%d\n",TwoOrSix(32));
	swap(10,20);
	printf("%d\n",SwapBits(14));
	
	return 0;
}


