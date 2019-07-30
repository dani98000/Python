#include "dhcp.h"
#include "trie.h"
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
int Test_StressTest();

int main()
{
	RUN_TEST(Test_DHCPCreate);
	RUN_TEST(Test_GetAddress);
	RUN_TEST(Test_StressTest);

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
	uint32_t res1 = 0;
	uint32_t res2 = 0;
	int result = 1;
	int res = 0;
	size_t test_no = 0;

	uint32_t subnet_mask = 0XFFFFFF00;
	ip_t net_add = 
	{
		{
			10,1,5,0 /* 167838976 */
		}
	};
	ip_t ip_req;
	ip_req.ip_addr[0] = 10;
	ip_req.ip_addr[1] = 1;
	ip_req.ip_addr[2] =	5;
	ip_req.ip_addr[3] = 8;
	dhcp = DHCPCreate(net_add, subnet_mask);
	
	/*test1*/
	GetAddress(dhcp, ip_req, &ip_res);
	res1 = CharToIPv(ip_res);
	TEST_EQUAL(res1, 167838984);

	/*test2*/
	res = DHCPCountFree(dhcp);
	TEST_EQUAL(res, 253);

	/*test3*/
	res = GetAddress(dhcp, ip_req, &ip_res2);
	TEST_EQUAL(res, 1);	
	res2 = CharToIPv(ip_res2);
	TEST_EQUAL(res2, 167838985);

	/*test4*/
	res = DHCPCountFree(dhcp);
	TEST_EQUAL(res, 252);

	FreeAddr(dhcp, ip_res);

	/*test6*/
	res = DHCPCountFree(dhcp);
	TEST_EQUAL(res, 253);

	/*test5*/
	GetAddress(dhcp, ip_req, &ip_res);
	res1 = CharToIPv(ip_res);
	TEST_EQUAL(res1, 167838984);

	

	DHCPDestroy(dhcp);


	return result;
}

int Test_StressTest()
{
	dhcp_t *dhcp = NULL;
	ip_t ip_res, ip_res2;
	uint32_t res1 = 0;
	uint32_t res2 = 0;
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	int i = 0;
	ip_t ip_req;

	uint32_t subnet_mask = 0XFFFFFF00;
	ip_t net_add = 
	{
		{
			10,1,5,0 /* 167838976 */
		}
	};

	dhcp = DHCPCreate(net_add, subnet_mask);

	for(i = 1; i < 255; ++i)
	{
		ip_req.ip_addr[0] = 10;
		ip_req.ip_addr[1] = 1;
		ip_req.ip_addr[2] =	5;
		ip_req.ip_addr[3] = i;
		GetAddress(dhcp, ip_req, &ip_res2);	
	}	

	/*test1*/
	res = DHCPCountFree(dhcp);
	TEST_EQUAL(res, 0);

	/*test3*/
	res = GetAddress(dhcp, ip_req, &ip_res2);
	TEST_EQUAL(res, 2);	
	

	DHCPDestroy(dhcp);


	return result;
}