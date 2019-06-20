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
int test_BARRRotateLeft();
int test_BARRRotateRight();
int test_BARRMirrorLUT();
int test_BARRCountOnLUT();


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
	RUN_TEST(test_BARRRotateLeft);
	RUN_TEST(test_BARRRotateRight);
	RUN_TEST(test_BARRMirrorLUT);
	RUN_TEST(test_BARRCountOnLUT);		
	
	printf("\n");
	
	if(test_BARRCountOn() && test_BARRCountOff() && test_BARRSetBit() && 
	   test_BARRMirror()  && test_BARRSetOn()    && test_BARRSetOff() && 
	   test_BARRIsOn()    && test_BARRIsOff() 	 && test_BARRFlip()   && 
	   test_BARRRotateLeft() && test_BARRRotateRight() && test_BARRMirrorLUT() && 			     	 	    test_BARRCountOnLUT())
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
	
	result *= (BARRMirror(1) == 9223372036854775808lu);
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
	result *= (BARRSetOn(0,33) == 8589934592);
	
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

int test_BARRRotateLeft()
{
	int result = 1;
	
	result *= (BARRRotateLeft(1,64) == 1);
	result *= (BARRRotateLeft(8,66) == 32);
	result *= (BARRRotateLeft(1,66) == 4);
	result *= (BARRRotateLeft(0,67) == 0);		
	
	return result;
}

int test_BARRRotateRight()
{
	int result = 1;
	
	result *= (BARRRotateRight(4,1) == 2);
	result *= (BARRRotateRight(0,5) == 0);
	result *= (BARRRotateRight(8,2) == 2);
	result *= (BARRRotateRight(32,64) == 32);
	result *= (BARRRotateRight(16,65) == 8);
	/*result *= (BARRRotateRight(0XBCDABCDFFFFFFFFA, 4) == 0XABCDABCDFFFFFFFF);*/
		
	return result;
}

int test_BARRMirrorLUT()
{
	int result = 1;
	
	result *= (BARRMirrorLUT(9223372036854775808lu) == 1);
	result *= (BARRMirrorLUT(4503599627370496) == 2048);
	result *= (BARRMirrorLUT(9007199254740992) == 1024);		
		
	return result;
}

int test_BARRCountOnLUT()
{
	int result = 1;
	
	result *= (BARRCountOnLUT(7) == 3);
	result *= (BARRCountOnLUT(15) == 4); 
	result *= (BARRCountOnLUT(0) == 0);
	result *= (BARRCountOnLUT(32) == 1);
	result *= (BARRCountOnLUT(8) == 1);
	
	return result;
}
