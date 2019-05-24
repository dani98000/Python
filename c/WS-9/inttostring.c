#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rev(int num);
char *IntToString(int num, char *buffer);
int StringToInt(char *string);
char *IntToString2(int num,char *buffer, int base);

int main()
{
	char *p=(char *)malloc(100*sizeof(char));
	char *s=(char *)malloc(100*sizeof(char));
	char string[]="123";
	p=IntToString(0,p);
	s=IntToString2(123,s,10);
	printf("%s\n",p);
	printf("%d\n",StringToInt(string));
	printf("%s\n",s);
	
	return 0;
}

char *IntToString(int num,char *buffer)
{
	char *runner=buffer;
	int newnum=rev(num);
	if(newnum == 0)
	{
		*runner ='0';
		++runner;
		*runner = '\0';
	}
	if (newnum<0)
	{
		*runner='-';
		++runner;
		newnum = -newnum;
	}
	while(newnum>0)
	{
		*runner = newnum % 10 + '0';
		newnum /= 10;
		++runner;
	}	
	*runner='\0';
	
	return (buffer);
}


int rev(int num)
{
	int reversedNumber = 0, carry = 0;

    while(num != 0)
    {
        carry = num%10;
        reversedNumber = reversedNumber*10 + carry;
        num /= 10;
    }

    return(reversedNumber);
}

int StringToInt(char *string)
{
	int num = 0, i, len;
	len = strlen(string);
	for(i=0; i<len; i++){
		num = num * 10 + ( string[i] - '0' );
	}
	return num;
}

char *IntToString2(int num,char *buffer, int base)
{
	char *runner=buffer;
	int newnum=rev(num);
	int carry = 0;
	while(newnum!=0)
	{
		carry = newnum / base;
		*runner = (carry > 9)? (carry-10) + 'a' : carry + '0'; 
		newnum /= base;
		++runner;
	}	
	*runner='\0';
	
	return (buffer);
}
