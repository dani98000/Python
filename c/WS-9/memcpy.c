#include <stdio.h> /* printf */ 

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
	
}


int main()
{
	int i = 0;
	const char src[50] = "My name is Daniellllllllllllll";
    char dest[50];
    memcpyV2(dest+1, src, 17);
    printf("%s\n",dest+1);
    for (; i < 30; i++)
	{
		printf("%p, %c\n",dest + i,*(dest + i));
	}
	
	for (i = 0 ;i < 30;i++)
	{
		printf("%p, %c\n",src + i,*(src + i));
	}
   
   
	return(0);
}
