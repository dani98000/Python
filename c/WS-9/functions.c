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
	
	while( ((size_t)((char*)str + i) % 8 != 0 ) && (n > 0))
	{
		*((char*)(str) + i) = c;
		/*printf("c was added to this address: %p\n",(char*)str+i);*/
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
	while(i < temp/8)
	{ 
		*(p + i) = block;
		/*printf("c2 was added to this address: %p\n",&p[i]);*/
		++i;
		n -= sizeof(size_t);
    }
    end = (char*)(p + i);
    i = 0;
	while(n > 0)
    {
		*(end + i) = c;
		/*printf("c3 was added to this address: %p\n",end+i);*/
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
	
	while( ((size_t)(dest) % 8 != 0 ) && (n > 0))
	{
		*dest = *src;
		/*printf("%c c was added to this address: %p\n",*src,dest);*/
		++dest;
		++src;
		--n;
	}
	
	temp = n - n % 8;
	runner_d = (size_t *)dest;
	runner_s = (size_t *)src;
	
	while(i < temp/8)
	{ 
		*runner_d = *runner_s;
		/*printf("%c c2 was added to this address: %p\n", *src, dest);*/
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
		/*printf("%c c3 was added to this address: %p\n", *src, dest);*/
		++dest;
		++src;
		--n;
	}
	*(dest)='\0';
	return 0;
}

