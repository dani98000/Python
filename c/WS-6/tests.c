#include <stdio.h>
#include "functions.h"

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

int test_pow2();
int test_IsPow2L();
int test_IsPow2();
int test_Plusone();
int test_ThreeSet();
int test_byte_mirror();
int test_TwoAndSix();
int test_TwoOrSix();
int test_SwapBits();
int test_Div16();
int test_swap();
int test_CountSetV2();
int test_Printfloat();
int test_byte_mirror2();
int test_CountSet();

int main()
{
	RUN_TEST(test_pow2);
	RUN_TEST(test_IsPow2L);
	RUN_TEST(test_IsPow2)
	RUN_TEST(test_Plusone);
	RUN_TEST(test_ThreeSet);
	RUN_TEST(test_byte_mirror);
	RUN_TEST(test_TwoAndSix);
	RUN_TEST(test_TwoOrSix);
	RUN_TEST(test_SwapBits);
	RUN_TEST(test_Div16);
	RUN_TEST(test_swap);
	RUN_TEST(test_CountSetV2);
	RUN_TEST(test_Printfloat);
	RUN_TEST(test_byte_mirror2);
	RUN_TEST(test_CountSet);	
	
	return 0;
}

int test_pow2()
{
	return(pow2(5, 2) == 20 && pow2(1, 2) == 4 && pow2(0, 0) == 0);
}

int test_IsPow2L()
{
	return(IsPow2L(1) == 1 && IsPow2L(16) == 1 && IsPow2L(24) == 0);
}

int test_IsPow2()
{
	return(IsPow2(1) == 1 && IsPow2(16) == 1 && IsPow2(24) == 0);
}

int test_Plusone()
{
	return(Plusone(5) == 6 && Plusone(0) == 1 && Plusone(64) == 65);
}

int test_ThreeSet()
{
	unsigned arr[6]={8, 5, 10, 12, 7, 14};
	return(ThreeSet(arr,6) == 0);
}

int test_byte_mirror()
{
	return(byte_mirror(1) == 2147483648);
}

int test_TwoAndSix()
{
	return(TwoAndSix(38) == 1 && TwoAndSix(53) == 0 && TwoAndSix(64) == 0);
}

int test_TwoOrSix()
{
	return(TwoOrSix(38) == 1 && TwoOrSix(64) == 0 && TwoOrSix(53) == 1);
}

int test_SwapBits()
{
	return(SwapBits(45) == 57);
}

int test_Div16()
{
	return(Div16(17) == 16 && Div16(48) == 48 && Div16(105) == 96);
}

int test_swap()
{
	unsigned int a = 10, b = 20; 
	swap(&a, &b); 
	return 1;
}

int test_CountSetV2()
{
	return(CountSetV2(7) == 3 && CountSetV2(15) == 4 && CountSetV2(0) == 0);
}

int test_CountSet()
{
	return(CountSet(7) == 3 && CountSet(15) == 4 && CountSet(0) == 0);
}

int test_Printfloat()
{
	Printfloat(-1);
	return 1;
}

int test_byte_mirror2()
{
	return (byte_mirror2(1) == 2147483648);
}

