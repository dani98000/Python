#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *memmoveV2(void *str1, const void *str2, size_t n)
{
	char *dest = (char *)str1;
	char *src = (char*)(const void*)str2;
	if(src<dest)
	{
	
	}
	if(src>dest)
	{
		
	}
	if(src=dest)
	{
	
	}
	while(n > 0)
	{
		*dest = *src;
		printf("%c c was added to this address: %p\n",*src,dest);
		++dest;
		++src;
		--n;
	}
	/**(dest)='\0';*/
	return 0;
}


int main()
{
	int i = 0;
    const char src[]  = "newstring";
	char *dest=(char *)malloc(100 * sizeof(char));
	dest=(char *)src+2;
	

    printf("Before memmove dest = %s, src = %s\n", dest, src);
    for (i=0; i < 30; i++)
	{
		printf("%p, %c\n",dest + i,*(dest + i));
	}
	printf("---------------------------------------------------------------------\n");
	for (i = 0 ;i < 30;i++)
	{
		printf("%p, %c\n",src + i,*(src + i));
	}
    memmoveV2(dest, src, 9);
    printf("After memmove dest = %s, src = %s\n", dest, src);
   
    for (i=0; i < 30; i++)
	{
		printf("%p, %c\n",dest + i,*(dest + i));
	}
	printf("---------------------------------------------------------------------\n");
	for (i = 0 ;i < 30;i++)
	{
		printf("%p, %c\n",src + i,*(src + i));
	}

    return(0);
}
