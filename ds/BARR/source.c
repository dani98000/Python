/*******************************************
 **           Author: Mishel Liberman     **
 **           Date: 27.05.19              **
 *******************************************/

#include <stdio.h> /*size_t*/

#include "barr.h"


size_t BARRSetOn(size_t arr, int index)
{
	return (arr | (1<<(index)));
}

size_t BARRSetOff(size_t arr, int index)
{
	return ((0 == (arr & 1<<(index))) ? arr : arr & (~(1<<(index))));
}

size_t BARRSetBit(size_t arr, int index, int value)
{
	
	return (0 == value ? BARRSetOff(arr, index) : BARRSetOn(arr, index));
}

size_t BARRFlip(size_t arr, int index)
{
	return (1 == BARRIsOn(arr, index) ? BARRSetOff(arr, index) : BARRSetOn(arr, index));
}

size_t BARRMirror(size_t arr)
{
	if(8 == sizeof(arr))
	{
		arr = ( ((arr & 0xFFFFFFFF00000000) >> 32) | ((arr & 0x00000000FFFFFFFF) << 32));
		arr = ( ((arr & 0xFFFF0000FFFF0000) >> 16) | ((arr & 0x0000FFFF0000FFFF) << 16));
		arr = ( ((arr & 0xFF00FF00FF00FF00) >> 8 ) | ((arr & 0x00FF00FF00FF00FF) << 8) );
		arr = ( ((arr & 0xF0F0F0F0F0F0F0F0) >> 4 ) | ((arr & 0x0F0F0F0F0F0F0F0F) << 4) );
		arr = ( ((arr & 0xCCCCCCCCCCCCCCCC) >> 2 ) | ((arr & 0x3333333333333333) << 2) );
		arr = ( ((arr & 0xAAAAAAAAAAAAAAAA) >> 1 ) | ((arr & 0X5555555555555555) << 1) );
	}
	else if(8 == sizeof(arr))
	{
		arr = ( ((arr & 0xFFFF0000) >> 16) | ((arr & 0x0000FFFF) << 16));
		arr = ( ((arr & 0xFF00FF00) >> 8 ) | ((arr & 0x00FF00FF) << 8) );
		arr = ( ((arr & 0xF0F0F0F0) >> 4 ) | ((arr & 0x0F0F0F0F) << 4) );
		arr = ( ((arr & 0xCCCCCCCC) >> 2 ) | ((arr & 0x33333333) << 2) );
		arr = ( ((arr & 0xAAAAAAAA) >> 1 ) | ((arr & 0X55555555) << 1) );
	}
	
	return arr;
}

int BARRIsOn(size_t arr, int index)
{
	return (0 == (arr & (1<<(index))) ? 0 : 1); 
}

int BARRIsOff(size_t arr, int index)
{
	return (0 == (arr & (1<<(index))) ? 1 : 0); 
}

size_t BARRRotateL(size_t arr, size_t amount)
{
	int i = 0;

	if(8 == sizeof(arr))
	{
		for(i = 0; i < (int)amount; ++i)
		{
			if(0 == (arr & 0x8000000000000000))
			{
				arr <<=1;
			}
			else
			{
				arr <<=1;
				arr = arr | 0x01;
			}
		}
	}
	else if(4 == sizeof(arr))
	{
		for(i = 0; i < (int)amount; ++i)
		{
			if(0 == (arr & 0x80000000))
			{
				arr <<=1;
			}
			else
			{
				arr <<=1;
				arr = arr | 0x01;
			}
		}
	}
	
	return arr;
}

size_t BARRRotateR(size_t arr, size_t amount)
{
	int i = 0;
	
	if(8 == sizeof(arr))
	{
		for(i = 0; i < (int)amount; ++i)
		{
			if(0 == (arr & 0x01))
			{
				arr >>=1;
			}
			else
			{
				arr >>=1;
				arr = arr | 0x8000000000000000;
			}
		}
	}
	else if(4 == sizeof(arr))
	{
		for(i = 0; i < (int)amount; ++i)
		{
			if(0 == (arr & 0x01))
			{
				arr >>=1;
			}
			else
			{
				arr >>=1;
				arr = arr | 0x80000000;
			}
		}
	}
	
	return arr;
}

size_t BARRCountOn(size_t arr)
{
	int times = 8 * sizeof(arr), counter = 0, i = 0;
	
	for(; i < times; ++i)
	{
		if(0 != (arr & 0x01))
		{
			++counter;
		}
		
		arr >>=1;
	}
	
	return counter;
}

size_t BARRCountOff(size_t arr)
{
	int times = 8 * sizeof(arr), counter = 0, i = 0;
	
	for(; i < times; ++i)
	{
		if(0 == (arr & 0x01))
		{
			++counter;
		}
		
		arr >>=1;
	}	
	
	return counter;
}



