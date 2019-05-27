#include "functions.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>


void *memsetV2(void *str, int c, size_t n)
{
	int i = 0, j = 0, temp = 0;
	size_t *p = NULL;
	size_t block = 0;
	char *end = NULL;
	
	while(((size_t)((char*)str + i) % 8 != 0 ) && (n > 0))
	{
		*((char*)(str) + i) = c;
		++i;
		--n;
	}
	
	p = (size_t *)((char *)str + i);
	temp = n - n % 8;

	for(j = 0; j < 8; ++j)
	{
		block ^= c;
		block <<= 8;
	}
	block ^= c;
	i = 0;
	
	while(i < temp / 8)
	{ 
		*(p + i) = block;
		++i;
		n -= sizeof(size_t);
    }
    
    end = (char*)(p + i);
    i = 0;
    
	while(n > 0)
    {
		*(end + i) = c;
		--n;
		++i;
	}
	
	return 0;
}		  


void *memcpyV2(void *str1, const void *str2, size_t n)
{
	char *dest = (char *)str1;
	char *src = (char *)str2;
	size_t *runner_d = NULL;
	size_t *runner_s = NULL;
	int temp = 0, i = 0;
	
	while(((size_t)(dest) % 8 != 0 ) && (n > 0))
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	
	temp = n - n % 8;
	runner_d = (size_t *)dest;
	runner_s = (size_t *)src;
	
	while(i < temp / 8)
	{ 
		*runner_d = *runner_s;
		++runner_d;
		++runner_s;
		++i;
		n -= sizeof(size_t);
    }
    
    dest= (char *)runner_d;
    src = (char *)runner_s;
    
	while(n > 0 )
    {
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	*(dest) = '\0';
	
	return 0;
}

void *memmoveV2(void *dest, void *src, size_t n)
{
	char *dest_r = (char *)dest + n - 1;
	char *dest_p = (char * )dest;
	char *src_r = (char *)src + n - 1;
	char *end = (char *)(dest) + n;
	
	if(dest < src)
	{
		memcpyV2(dest, src, n);
	}
	
	while(n > 0 && dest_r > dest_p)
	{
		*dest_r = *src_r;
		--src_r;
		--dest_r;
		--n;
	}	
	*dest_p = *src_r;
	*(end) = '\0';
	
	return 0;
}
