#include <stdio.h>
#include <stdlib.h>

int rev(int num);
char *IntToString(int num, char *buffer);

int main()
{
	char *p=(char *)malloc(100*sizeof(char));
	printf("%d\n",(*IntToString(123,p)));
	printf("%d\n",*p);
	
	return 0;
}

char *IntToString(int num,char *buffer)
{
	char *runner=buffer;
	int newnum=rev(num);
	while(newnum>0)
	{
		*runner = newnum % 10;
		newnum /= 10;
		++runner;
	}	
	*runner='\0';
	
	return (buffer);
}


int rev(int num)
{
	int reversedNumber = 0, remainder;

    while(num != 0)
    {
        remainder = num%10;
        reversedNumber = reversedNumber*10 + remainder;
        num /= 10;
    }

    return(reversedNumber);
}
