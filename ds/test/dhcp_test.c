#include "dhcp.h"
#include "bt.h"
#include "ip.h"

#include <stdint.h> /* uint32_t */
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

int Test_DHCPCreate();
int Test_GetAddress();

int main()
{
	RUN_TEST(Test_DHCPCreate);
	RUN_TEST(Test_GetAddress);

	return 0;
}

int Test_DHCPCreate()
{
	dhcp_t *dhcp = NULL;
	uint32_t subnet_mask = 0XFFFFFF00;
	ip_t net_add = 
	{
		{
			10,1,5,0
		}
	};
	dhcp = DHCPCreate(net_add, subnet_mask);
	DHCPDestroy(dhcp);
	return 1;
}

int Test_GetAddress()
{
	dhcp_t *dhcp = NULL;
	ip_t ip_res, ip_res2;
	uint32_t res = 0;
	uint32_t res2 = 0;

	uint32_t subnet_mask = 0XFFFFFF00;
	ip_t net_add = 
	{
		{
			10,1,5,0
		}
	};
	ip_t ip_req;
	ip_req.ip_addr[0] = 10;
	ip_req.ip_addr[1] = 1;
	ip_req.ip_addr[2] =	5;
	ip_req.ip_addr[3] = 8;
	dhcp = DHCPCreate(net_add, subnet_mask);
	
	GetAddress(dhcp, ip_req, &ip_res);
	res = IPIpv4ToNum(ip_res);
	printf("%x\n", res);

	GetAddress(dhcp, ip_req, &ip_res2);
	res2 = IPIpv4ToNum(ip_res2);
	printf("%x\n", res2);

	FreeAddr(dhcp, ip_res);

	GetAddress(dhcp, ip_req, &ip_res);
	res = IPIpv4ToNum(ip_res);
	printf("%x\n", res);

	DHCPDestroy(dhcp);


	return 1;

}