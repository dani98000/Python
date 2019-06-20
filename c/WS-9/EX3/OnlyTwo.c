#include <stdio.h>  /* printf */
#include <stdlib.h> /* calloc */

void OnlyTwo(char arr1[],char arr2[], char arr3[],int size1, int size2, int size3);

int main()
{
	char arr1[]="abcdefgh";
	char arr2[]="acefh";
	char arr3[]="lojac";
	OnlyTwo(arr1,arr2,arr3,8,5,5);
	
	return 0;	
}

void OnlyTwo(char arr1[],char arr2[], char arr3[],int size1, int size2, int size3)
{
	char *LUT = calloc(256, sizeof(char));
	int i = 0;
	for(i = 0;i < size1;i++)
	{
		LUT[(int)arr1[i]] = LUT[(int)arr1[i]]|0x1;
	}
	for(i = 0;i < size2;i++)
	{
		LUT[(int)arr2[i]] = LUT[(int)arr2[i]]|0x2;
	}
	for(i = 0;i < size3;i++)
	{
		LUT[(int)arr3[i]] = LUT[(int)arr3[i]]|0x4;
	}
	
	for(i = 0; i < 256; i++)
	{
		if(LUT[i] == 3)
		{
			printf("%c\n",i);
		}
	}
	
}
