#include <stdio.h>
#include <stdlib.h>

#define Esc 27

void Switch();
void If();
void Apressed(); 
void Tpressed();
void EmptyFunction();
void PrintLUT();

int main()
{
	/*Switch();
	If();*/
	PrintLUT();

	return 0;
}

void Switch(void)
{
	char c;
	system("stty -icanon -echo");
	c = getchar();
	
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
		
		case Esc:
			printf("Byeeeeeeeeeeee\n");
		break;
		
		default:
			printf("Error! Invalid key entered.\n");
			Switch();
		break;
	}

	system("stty icanon echo");
}

void If()
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
	else if(Esc == c)
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

void PrintLUT()
{
	void (*pointer_arr[256])(void);
	unsigned char x = 0;
	int i = 0;
	
	for(; i < 256; i++)
	{
		if(i == 'A' || i == 'a')
		{
			pointer_arr[i]=Apressed;
		}
		else if(i == 'T' || i == 't')
		{
			pointer_arr[i] = Tpressed;
		}
		else
		{
			pointer_arr[i] = EmptyFunction;
		}
	}
	
	system("stty -icanon -echo");
	x = getchar();

	while(x != Esc)
	{
		x = getchar();
		pointer_arr[(unsigned int)x]();
	}
	
	system("stty icanon echo");
}

void Apressed()
{
	printf("A pressed\n");
}

void Tpressed()
{
	printf("T pressed\n");
}

void EmptyFunction()
{
	;
}
