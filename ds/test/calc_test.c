#include <stdio.h>

#include "../include/parser.h"

#define TEST_STATUS(status, expected) \
++test_no; ++g_total_tests;\
printf("\ttest %lu: expected: %d, got: %d\n",\
test_no, expected, status); result *= (expected == status); \
(expected == res) ? (++g_total_success) : (++g_total_failed);

#define TEST_RES(res, expected) \
++test_no; ++g_total_tests;\
printf("\ttest %lu: expected: %d, got: %f\n",\
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

int Test_AddAndMult();
int Test_SubAndDiv();
int Test_Pow();

int main()
{
	RUN_TEST(Test_AddAndMult);
	RUN_TEST(Test_SubAndDiv);
	RUN_TEST(Test_Pow);
	
	return 0;
}

int Test_AddAndMult()
{
	int result = 1;
	int status = 0;
	double res = 0;
	size_t test_no = 0;
	char *str1 = "6+2*4";
	char *str2 = "5*5+2";
	
	
	/* TEST1 */
	status = Calculate(str1 , &res);
	printf("\t\t\t%s\n", str1);
	TEST_RES(res, 14);
	TEST_STATUS(status, 0);	
	
	printf("\n\n");
	
	/* TEST1 */
	status = Calculate(str2 , &res);
	printf("\t\t\t%s\n", str2);
	TEST_RES(res, 27);
	TEST_STATUS(status, 0);		
	
	return result;
}

int Test_SubAndDiv()
{
	int result = 1;
	int status = 0;
	double res = 0;
	size_t test_no = 0;
	char *str1 = "5*4/2";
	char *str2 = "20-5/5";
	
	
	/* TEST1 */
	status = Calculate(str1 , &res);
	printf("\t\t\t%s\n", str1);
	TEST_RES(res, 10);
	TEST_STATUS(status, 0);	
	
	printf("\n\n");
	
	/* TEST1 */
	status = Calculate(str2 , &res);
	printf("\t\t\t%s\n", str2);
	TEST_RES(res, 19);
	TEST_STATUS(status, 0);
	
	return result;		
}

int Test_Pow()
{
	int result = 1;
	int status = 0;
	double res = 0;
	size_t test_no = 0;
	char *str1 = "5*4^2";
	char *str2 = "5^2*5+5";
	char *str3 = "5+2^2^3";
	
	/* TEST1 */
	status = Calculate(str1 , &res);
	printf("\t\t\t%s\n", str1);
	TEST_RES(res, 80);
	TEST_STATUS(status, 0);	
	
	printf("\n\n");
	
	/* TEST1 */
	status = Calculate(str2 , &res);
	printf("\t\t\t%s\n", str2);
	TEST_RES(res, 130);
	TEST_STATUS(status, 0);

	printf("\n\n");
	
	/* TEST1 */
	status = Calculate(str3 , &res);
	printf("\t\t\t%s\n", str3);
	TEST_RES(res, 261);
	TEST_STATUS(status, 0);
	
	return result;		

}
