#include <stdio.h>
#include <stdlib.h>

#include "../../include/CBUF/cbuf.h"

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

/*int Test_DvecPeek(void);
int Test_DvecPop(void);
int Test_DvecPush(void);
int Test_DvecSizeUp(void);
int Test_DvecSizeDown(void);
int Test_DvecReserve(void);
*/
void test_create()
{
	cbuf_t *cbuf = NULL;
	size_t expected = 5;
	char *field = NULL;
	char dest[5] = "hello";
	
	cbuf = CBUFCreate(50);
	printf("%d",CBUFWrite(cbuf,dest,1));
	
	CBUFDestroy(cbuf);
}

int main()
{	
	test_create();

	
	return 0;
}

