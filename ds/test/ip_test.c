#include "ip.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* malloc */

#define CLEAR "\033[0m"
#define GREEN "\x1B[32m"
#define RED   "\x1B[31m"
#define CYAN  "\x1B[36m"

#define TEST_EQUAL(res, expected) \
++test_no; ++g_total_tests;\
printf("\ttest %lu: expected: %d, got: %d\n",\
test_no, expected, res); result *= (expected == res); \
(expected == res) ? (++g_total_success) : (++g_total_failed);

#define TEST_SUMMARY(tot, success, fail) \
printf(CYAN "\nTest Result Summary:\n" CLEAR); \
printf("Total:     %lu [100.0%%]\n", tot); \
printf(RED "Failed:     %lu [%.1f%%]\n" CLEAR, fail, \
((float)fail / tot) * 100); \
printf(GREEN "Succeeded: %lu [%.1f%%]\n" CLEAR, success, \
((float)success / tot) * 100);


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

size_t g_total_tests = 0;
size_t g_total_success = 0;
size_t g_total_failed = 0;

int Test_IPIpv4ToNum();
int Test_IPNumToIpv4();

int main()
{
	RUN_TEST(Test_IPIpv4ToNum);
	RUN_TEST(Test_IPNumToIpv4);

	/*uint32_t x = 0;
	ip_t ip;
	ip.ip_addr[0] = 255;
	ip.ip_addr[1] = 255;
	ip.ip_addr[2] = 255;
	ip.ip_addr[3] = 0;
	x = IPIpv4ToNum(ip);
	printf("%u", x);
*/
	return 0;
}

int Test_IPIpv4ToNum()
{
	ip_t ip1;
	uint32_t x = 0;
	int result = 1;
	int res = 0;
	size_t test_no = 0;

	ip1.ip_addr[0] = 255;
	ip1.ip_addr[1] = 255;
	ip1.ip_addr[2] = 255;
	ip1.ip_addr[3] = 0;
	
	x = IPIpv4ToNum(ip1);
	
	return x == 0XFFFFFF00;
}

int Test_IPNumToIpv4()
{
	ip_t ip1;
	uint32_t x = 0XFFFFFF00;
	int result = 1;
	int res = 0;
	size_t test_no = 0;

	ip1 = IPNumToIpv4(x);
	printf("%u",ip1.ip_addr[0]);
	printf("%u",ip1.ip_addr[1]);
	printf("%u",ip1.ip_addr[2]);
	printf("%u",ip1.ip_addr[3]);


	return result;
}