#include <stdio.h>

#define ISL (char *

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
}
