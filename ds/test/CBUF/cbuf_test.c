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
	char a = '5';
	char dest[] = {'\0','\0'};
	
	cbuf = CBUFCreate(50);
	CBUFWrite(cbuf,&a,1);
	
	CBUFRead(cbuf,dest,1);
		printf("%s",dest);
	CBUFDestroy(cbuf);
}

int main()
{	
	test_create();

	
	return 0;
}

