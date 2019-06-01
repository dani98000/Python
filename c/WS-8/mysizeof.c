#include <stdio.h> /* printf */

#define RUN_TEST(test)\
if(!test())\
{\
printf("\033[1;31m");\
printf(#test " - failed!\n");\
printf("\033[0m");\
}\
else\
{\
printf("\033[1;32m");\
printf(#test " - ok!\n");\
printf("\033[0m");\
}

#define SOV(x) (char *)(&x+1)-(char*)(&x)
#define SOT(type)  (int)((type *)1 + 1) - (int)(type *)1

int TestSOV();
int TestSOT();

int main()
{
	RUN_TEST(TestSOV);
	RUN_TEST(TestSOT);

	return 0;	
}

int TestSOV()
{
	char c;
	short int s;
	int i;
	unsigned int u;
	
	return (SOV(c) == sizeof(c)
			&& SOV(s) == sizeof(s)
			&& SOV(i) == sizeof(i)
			&& SOV(u) == sizeof(u));
}

int TestSOT()
{
	return (SOT(char) == sizeof(char)
			&& SOT(short int) == sizeof(short int)
			&& SOT(int) == sizeof(int)
			&& SOT(unsigned int) == sizeof(unsigned int));
}

