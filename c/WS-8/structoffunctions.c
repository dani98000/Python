#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string.h>
#define UNUSED(x) (void)(x)

void AddInt(int Input, void *data);
void AddFloat(int Input, void *data);
void AddString(int Input, void *data);
void PrintInt(void *data);
void PrintFloat(void *data);
void PrintString(void *data);
void FreeMemory(void *data);
void DoNothing(void *data);

struct functions
{
    void *data;
	void (*Add)(int Input, void *data);
	void (*Print)(void *data);
	void (*Free_memory)(void *data);
};

int main()
{
	struct functions array[3]= 
	{  
	   	{(void *)0, AddInt, PrintInt, DoNothing},
	   	{(void *)0, AddFloat, PrintFloat, DoNothing},
   		{(void *)NULL, AddString, PrintString, FreeMemory},
	};
	
	int a1 = 5;
	int a2 = 6;

	float b1 = 1.5;
	float b2 = 2.2;

	char c1 = 'a';
	char c2 = 's';

	array[2].data=(char *)calloc(100, sizeof(char));
	array[1].data = (void *)*(int *)&b1;
	
	array[0].Add(a1, &(array[0].data));
	array[0].Print(array[0].data);
	array[0].Add(a2, &(array[0].data));
	array[0].Print(array[0].data);
	array[1].Add(b1, &(array[1].data));
	array[1].Print(array[1].data);
	array[1].Add(b2, &(array[1].data));
	array[1].Print(array[1].data);
	array[2].Add(c1, &(array[2].data));
	array[2].Print(array[2].data);
	array[2].Add(c2, &(array[2].data));
	array[2].Print(array[2].data);	
	free(array[2].data);

	return 0;
}

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


