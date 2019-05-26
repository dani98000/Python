#include <stdio.h>

#define ISL *(char *) "\x01\x00" == (char) 1

int IsLittleEndian()
{
	unsigned int i=1;
	char *p= (char*)(&i);
	return (*p);
}

int main()
{
	if(IsLittleEndian())
	{
		printf("Is little endian\n");
	}
	else
	{
		printf("Is big endian\n");
	}
	printf("%d\n",ISL);
	return 0;
}
