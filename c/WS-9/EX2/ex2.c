#include <stdio.h> /* printf  */
#include <stdlib.h>/* malloc  */
#include <string.h>/* strlen  */
#include <math.h>  /* pow     */
#include <ctype.h> /* isdigit */

#include "functions.h"

char *MyItoa(int num,char *buffer)
{
	char *runner = buffer;
	int newnum = rev(num);
	if(newnum == 0)
	{
		*runner ='0';
		++runner;
		*runner = '\0';
	}
	if (newnum < 0)
	{
		*runner = '-';
		++runner;
		newnum = -newnum;
	}
	while(newnum > 0)
	{
		*runner = newnum % 10 + '0';
		newnum /= 10;
		++runner;
	}	
	*runner = '\0';
	
	return (buffer);
}


int rev(int num)
{
	int reversedNumber = 0, carry = 0;

    while(num != 0)
    {
        carry = num % 10;
        reversedNumber = reversedNumber * 10 + carry;
        num /= 10;
    }

    return(reversedNumber);
}

int MyAtoi(char *string)
{
	int num = 0, i=0, len;
	len = strlen(string);
	if(*string == '-')
	{
		i = 1;
	}
	
	for(; i < len; i++){
		num = num * 10 + ( string[i] - '0' );
	}
	if(*string == '-')
	{
		num = -num;
	}
	return num;
}
void reverse(char str[], int length) 
{ 
    int i = 0;
    int end = length -1; 
    int temp = 0;
    
    for(i = 0; i < length / 2; i++)
    {
    	temp = *(str + i);
		*(str + i) = *(str + end);
		*(str+end) = temp;
		--end;
    } 
} 

char *MyItoaV2(int num, char *buffer, int base)
{
	char *runner = buffer;
	int carry = 0;
	int IsNeg = 0;
	if (num < 0)
	{
		IsNeg=1;
		*runner = '-';
		++runner;
		num = -num;
	}
	
	while(num != 0)
	{
		carry = num % base;
		if(carry > 9)
		{
			*runner = carry-10 + 'A';
		}
		else
		{
			*runner = carry + '0';
		} 
		num /= base;
		++runner;
	}
	*runner = '\0';
	if(1 == IsNeg)
	{
		reverse(buffer+1, runner - buffer-1);
	}
	else
	{
		reverse(buffer, runner - buffer);
	}

	return (buffer);
}

int MyAtoiV2(char *string, int base)
{
	int num = 0, i = 0, j = 0, len;
	int signal = 1;
	len = strlen(string);
	if(*string == '-')
	{
		signal = -1;
		++string;
		--len;
	}
	for(i = len-1; i >=0; --i)
	{
		if(isdigit(string[i]))
		{
			num = num + ((string[i]-'0')*(pow(base,j)));
		}
		else
		{
			num = num + (string[i]-'7')*(pow(base,j));
		}
		++j;
	}
	
	return (num*signal);
}
