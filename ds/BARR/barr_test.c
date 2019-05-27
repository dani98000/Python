#include <stdio.h>

#include "barr.h"

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

int test_BARRCountOn();
int test_BARRCountOff();
int test_BARRSetBit();
int test_BARRMirror();
int test_BARRSetOn();
int test_BARRIsOn();
int test_BARRIsOff();


int main()
{
	RUN_TEST(test_BARRCountOn);	
	RUN_TEST(test_BARRCountOff);
	RUN_TEST(test_BARRSetBit);	
	RUN_TEST(test_BARRMirror);	
	RUN_TEST(test_BARRSetOn);
	RUN_TEST(test_BARRIsOn);
	RUN_TEST(test_BARRIsOff);
		
	return 0;
}

int test_BARRCountOn()
{
	return(BARRCountOn(7) == 3 && BARRCountOn(15) == 4 && BARRCountOn(0) == 0);
}

int test_BARRSetBit()
{
printf("%lu",BARRSetBit(3,1,0));
	return(BARRSetBit(0, 0, 1) == 1 && BARRSetBit(16, 4, 0) == 0 && BARRSetBit(15,3,0) == 7);
}

int test_BARRMirror()
{
	return(BARRMirror(1) == 2147483648);
}

int test_BARRSetOn()
{
	return(BARRSetOn(0,4) == 16 && BARRSetOn(2,0) == 3 && BARRSetOn(0,0) == 1	);
	
}

int test_BARRCountOff()
{
	return(BARRCountOff(0) == 64 && BARRCountOff(1) == 63 && BARRCountOff(9) == 62);
}

int test_BARRIsOn()
{
	printf("%ld\n",(BARRIsOn(8,3)));
	return(BARRIsOn(8,3) == 1);
}

int test_BARRIsOff()
{
	return(BARRIsOff(1,0) == 0 && BARRIsOff(7,3) == 1);
}
