/****************************
*   Author: Daniel Maizel	*	
*	Reviewer: 				*				
*	Date: 19/05/2019		*		
*							*
*****************************/

#include <stdio.h>


double pow2(unsigned int x, int y)
{
	double res = x << y;
	
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
		temp = temp >> 1;
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
	if((n & 1) == 1)
	{
		n = -(~n);	
	}
	else
	{
		n = n | (1 << 0);
	}
	
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
	for(i = 0; i < arr_length; ++i)
	{
		temp = arr[i];
		while(temp >= 1 ) 
		{	
			if((temp & 1) == 1)
			{
				++count;
			}
			temp = temp >> 1;
		}
		if(count == 3)
		{
			printf("%d\n", arr[i]);
		}
		count = 0;
	}
	
	return 0;
}
	
	
unsigned int byte_mirror(unsigned int num)
{
	unsigned int mirror = 0;
	int i;
	for(i = 0; i < 32; ++i)
	{
		mirror = mirror | ((num >> i) & 1) << (31 - i); 
	}
	
	return mirror;
}

unsigned int byte_mirror2(unsigned int num)
{
	num = ((num & 0xffff0000) >> 16) | ((num & 0x0000ffff) << 16);
	num = ((num & 0xff00ff00) >>  8) | ((num & 0x00ff00ff) <<  8);
	num = ((num & 0xf0f0f0f0) >>  4) | ((num & 0x0f0f0f0f) <<  4);
	num = ((num & 0xcccccccc) >>  2) | ((num & 0x33333333) <<  2);
	num = ((num & 0xaaaaaaaa) >>  1) | ((num & 0x55555555) <<  1);
	
	return num;
}

unsigned int Div16(unsigned int a)
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
		num = num >> 1;
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

int swap(unsigned int x, unsigned int y)
{
	x = x ^ y; 
    y = x ^ y; 
    x = x ^ y;
    printf("x = %d\ny = %d\n", x, y);
    
    return 1;
}

int SwapBits(unsigned int num) 
{ 
    unsigned int bit1 =  (num >> 2) & 1; 
    unsigned int bit2 =  (num >> 4) & 1; 
    unsigned int x = (bit1 ^ bit2); 
    unsigned int result;
    x = (x << 2) | (x << 4); 
	result = num ^ x;
	 
    return result;
} 

int CountSetV2(unsigned int num)
{
    int bits[] = {1, 2, 4, 8, 16};
    int masks[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};
 
    int count = num - ((num >> 1) & masks[0]);
    count = ((count >> bits[1]) & masks[1]) + (count & masks[1]);
    count = ((count >> bits[2]) + count) & masks[2];
    count = ((count >> bits[3]) + count) & masks[3];
    count = ((count >> bits[4]) + count) & masks[4];
    
    return count;
}


	
void Printfloat(float num)
{
	int *ptr = (int *)&num;
	int k;
    for (k = 31; k >= 0; --k) 
    { 
 
        if ((*ptr >> k) & 1)
        { 
            printf("1");
        } 
        else
        {
            printf("0");
        } 
	}
	printf("\n");
}

