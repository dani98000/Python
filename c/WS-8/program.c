#include <stdio.h>
#define sof(x) (char *)(&x+1)-(char*)(&x)

int g1;
static int g2;
static int g3 = 0;
static int g4 = 8;

static void foo1()
{
	static int g5;
	int l1 = 9;
}

void foo2()
{
	static int g6 = 0;
	static int g7 = 0;
}

extern void bar();

int main()
{
	printf("%ld,%ld\n",sof(int),sizeof(int));
	return 0;
}
