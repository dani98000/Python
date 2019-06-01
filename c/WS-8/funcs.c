#include "ex8.h"
#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */
#include <string.h>

#define UNUSED(x) (void)(x)

void AddInt(int Input, void *data)
{
	*(int *)data = (Input + *(int*)data);
}

void AddFloat(int Input, void *data)
{
	*(float *)data =((float)Input + *(float*)data); 
}

void AddString(int Input, void *data)
{
	char *buffer = (char *)calloc(100, sizeof(char));
	sprintf(buffer, "%c", Input);
	strcat(*((char **)data), buffer);
	free(buffer);
}

void PrintInt(void *data)
{
	printf("%d\n",(int)(data));
}

void PrintFloat(void *data)
{
	printf("%f\n",*(float *)(&data));
}

void PrintString(void *data)
{
	printf("%s",(char *)(data));
}

void FreeMemory(void *data)
{
	UNUSED(data);
	
	return;
}

void DoNothing(void *data)
{
	UNUSED(data);
	
	return;
}


