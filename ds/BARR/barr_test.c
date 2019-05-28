#include <stdio.h>/* printf */

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
int test_BARRSetOff();
int test_BARRIsOn();
int test_BARRIsOff();
int test_BARRFlip();
int test_BARRRotateL();
int test_BARRRotateR();
int test_BARRMirrorLut();


int main()
{
	RUN_TEST(test_BARRCountOn);	
	RUN_TEST(test_BARRCountOff);
	RUN_TEST(test_BARRSetBit);	
	RUN_TEST(test_BARRMirror);	
	RUN_TEST(test_BARRSetOn);
	RUN_TEST(test_BARRSetOff);
	RUN_TEST(test_BARRIsOn);
	RUN_TEST(test_BARRIsOff);
	RUN_TEST(test_BARRFlip);
	RUN_TEST(test_BARRRotateL);
	RUN_TEST(test_BARRRotateR);
	RUN_TEST(test_BARRMirrorLut);
	
	printf("\n");
	
	if(test_BARRCountOn() && test_BARRCountOff() && test_BARRSetBit() && 
	   test_BARRMirror()  && test_BARRSetOn()    && test_BARRSetOff() && 
	   test_BARRIsOn()    && test_BARRIsOff() 	 && test_BARRFlip()   && 
	   test_BARRRotateL() && test_BARRRotateR())
	{
		printf("\033[1;32m|All Tests were Passed Successfuly| \033[0m\n");
	}
	
	return 0;
}

int test_BARRCountOn()
{
	int result = 1;
	
	result *= (BARRCountOn(7) == 3);
	result *= (BARRCountOn(15) == 4); 
	result *= (BARRCountOn(0) == 0);
	result *= (BARRCountOn(32) == 1);
	
	return result;
}

int test_BARRSetBit()
{
	int result = 1;
	
	result *= (BARRSetBit(0, 0, 1) == 1); 
	result *= (BARRSetBit(16, 4, 0) == 0); 	
	result *= (BARRSetBit(15,3,0) == 7);
	result *= (BARRSetBit(0,5,1) == 32);
	
	return result;
}

int test_BARRMirror()
{
	int result = 1;
	
	result *= (BARRMirror(1) == 9223372036854775808);
	result *= (BARRMirror(4294967296) == 2147483648);
	result *= (BARRMirror(4503599627370496) == 2048);
	result *= (BARRMirror(9007199254740992) == 1024);		
	
	return result;
}

int test_BARRSetOn()
{
	int result = 1;
	
	result *= (BARRSetOn(0,4) == 16); 
	result *= (BARRSetOn(2,0) == 3);
	result *= (BARRSetOn(0,0) == 1);
	result *= (BARRSetOn(15,4) == 31);
	
	return result;
}

int test_BARRSetOff()
{
	int result = 1;
	
	result *= (BARRSetOff(7,2) == 3);
	result *= (BARRSetOff(16,4) == 0);
	result *= (BARRSetOff(15,0) == 14);
	result *= (BARRSetOff(1,0) == 0);
	
	return result;
}

int test_BARRCountOff()
{
	int result = 1;
	
	result *= (BARRCountOff(0) == 64);
	result *= (BARRCountOff(1) == 63);
	result *= (BARRCountOff(9) == 62);
	result *= (BARRCountOff(15) == 60);
	
	return result;
}

int test_BARRIsOn()
{
	int result = 1;
	
	result *= (BARRIsOn(8,3) == 1);
	result *= (BARRIsOn(16,4) == 1);
	result *= (BARRIsOn(8,4) == 0);
	result *= (BARRIsOn(1,1) == 0);			
	
	return result;
}

int test_BARRIsOff()
{
	int result = 1;
	
	result *= (BARRIsOff(1,0) == 0); 
	result *= (BARRIsOff(7,3) == 1);
	result *= (BARRIsOff(15,4) == 1);
	result *= (BARRIsOff(16,1) == 1);	
	
	return result;
}

int test_BARRFlip()
{
	int result = 1;
	
	result *= (BARRFlip(8,3) == 0);
	result *= (BARRFlip(7,3) == 15);
	result *= (BARRFlip(0,4) == 16);
	result *= (BARRFlip(1,0) == 0);
				
	return result;
}

int test_BARRRotateL()
{
	int result = 1;
	
	result *= (BARRRotateL(1,64) == 1);
	result *= (BARRRotateL(8,66) == 32);
	result *= (BARRRotateL(1,66) == 4);
	result *= (BARRRotateL(0,67) == 0);		
	
	return result;
}

int test_BARRRotateR()
{
	int result = 1;
	
	result *= (BARRRotateR(4,1) == 2);
	result *= (BARRRotateR(0,5) == 0);
	result *= (BARRRotateR(8,2) == 2);
	result *= (BARRRotateR(32,64) == 32);
	result *= (BARRRotateR(16,65) == 8);	
		
	return result;
}

int test_BARRMirrorLut()
{
	int result = 1;
	
	result *= (BARRMirrorLut(9223372036854775808) == 1);
	result *= (BARRMirrorLut(4503599627370496) == 2048);
	result *= (BARRMirrorLut(9007199254740992) == 1024);		
		
	return result;
}
