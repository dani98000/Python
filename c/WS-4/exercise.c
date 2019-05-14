#include <stdio.h>
#include <stdlib.h>

void Switch(void);
void If(void);
void Apressed(void);
void Tpressed();
void EmptyFunction(void);

int main()
{
	/*Switch();
	If();*/
	void (*pointer_arr[256])(void);
	unsigned char x = 0;
	int i=0;
	
	
	for(; i<256; i++)
	{
		if(i == 'A' || i == 'a')
		{
			pointer_arr[i]=Apressed;
		}
		else if(i == 'T' || i == 't')
		{
			pointer_arr[i]=Tpressed;
		}
		else
		{
			pointer_arr[i]=EmptyFunction;
		}
	}
		system("stty -icanon -echo");
		x=getchar();



	while(x != 27)
	{
		x=getchar();
		pointer_arr[(unsigned int)x]();
	}
	system("stty icanon echo");
	return 0;
}

void Switch(void)
{
	char c;
	system("stty -icanon -echo");
	c=getchar();
	
	switch(c)
	{
		case 'A':
		printf("A pressed\n");
		Switch();
		break;
		
		case 'T':
		printf("T pressed\n");
		Switch();
		break;
		
		case 27:
		printf("Byeeeeeeeeeeee\n");
		break;
		
		default:
		printf("Error! Invalid key entered.\n");
		Switch();
		break;
	}

	system("stty icanon echo");
}

void If(void)
{
	char c;
	system("stty -icanon -echo");
	c=getchar();
	
	if ('A' == c)
	{
		printf("A pressed\n");
		If();
	}
	else if('T' == c)
	{
		printf("T pressed\n");
		If();
	}	
	else if(27 == c)
	{
		printf("Byeeeeeeeeeeee\n");
	}	
	else
	{
		printf("Error! Invalid key entered.\n");
		If();
	}
	
	system("stty icanon echo");
}

void Apressed()
{
	printf("A pressed");
}

void Tpressed()
{
	printf("T pressed");
}

void EmptyFunction()
{
	;
}
