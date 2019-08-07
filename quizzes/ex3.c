#include <stdio.h>
#include <string.h>

int IsFound(char *arr, char key)
{
	char temp[2];
	temp[0] = key;
	temp[1] = '\0';
	return strstr(arr,temp) != NULL;
}

int main()
{
	char *arr = "daniel";
	char key = 'd';
	printf("%d\n",IsFound(arr, key));

	return 0;
}