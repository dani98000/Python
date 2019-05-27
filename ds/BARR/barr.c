/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer:					*
*								*
*********************************/

#include <stdio.h>
#include <assert.h>

#include "barr.h"

size_t BARRSetBit(size_t arr, int index, int value)
{
	size_t mask = 1;
	size_t mask2 = 1 << index; 
	int temp = 0;
	mask = mask << index;

	
	assert(value <= 1 && value >=0);
	if(value == 1)
	{
		temp = (1 << index) | arr;
	}
	else
	{
		temp = (0 << index) | arr;
	}
	
	return temp;
}

size_t BARRSetOn(size_t arr, int index)
{
	size_t temp = 0;
	temp = ((1 << index) | arr);
	
	return temp;
}

size_t BARRSetOff(size_t arr, int index)
{
	size_t mask = 1;
	mask = mask << index;
	if(((arr << index) & 1) == 1)
	{
		(arr << index) == (arr << index) ^ mask;
	}
	else
	{
		(arr << index) == (arr << index) | mask;
	}
	
	return arr;
}

size_t BARRFlip(size_t arr, int index)
{
	int temp = 0; 
	temp = (1 << index) | 0x1;
	
	return temp;
}

size_t BARRMirror(size_t arr)
{
	arr = ((arr & 0xffff0000) >> 16) | ((arr & 0x0000ffff) << 16);
	arr = ((arr & 0xff00ff00) >>  8) | ((arr & 0x00ff00ff) <<  8);
	arr = ((arr & 0xf0f0f0f0) >>  4) | ((arr & 0x0f0f0f0f) <<  4);
	arr = ((arr & 0xcccccccc) >>  2) | ((arr & 0x33333333) <<  2);
	arr = ((arr & 0xaaaaaaaa) >>  1) | ((arr & 0x55555555) <<  1);
	
	return arr;
}

int BARRIsOn(size_t arr, int index)
{
	return(((arr << index) & 1) == 1);
}

int BARRIsOff(size_t arr, int index)
{
	return(((arr << index) & 1) == 0);
}

size_t BARRRotateL(size_t arr, size_t amount)
{
	amount = amount % (sizeof(arr)*8);
	arr <<= amount;
	return arr; 
}

size_t BARRRotateR(size_t arr, size_t amount)
{
	amount = amount % (sizeof(arr)*8);
	arr >>= amount;
	
	return arr; 
}

size_t BARRCountOn(size_t arr)
{
	int count = 0;
	
	while(arr >= 1) 
	{	
		if((arr & 1) == 1)
		{
			++count;
		}
		arr = arr >> 1;
	}
	
	return count;
}

size_t BARRCountOff(size_t arr)
{
	int count = 0;
	
	while(arr >= 1) 
	{	
		if((arr & 1) == 1)
		{
			++count;
		}
		arr = arr >> 1;
	}
	
	return ((sizeof(size_t)*8)-count);

}
