#include <stdio.h>
#include <stdlib.h> /* strtod */

#include "../include/parser.h"

#define UNUSED(X) (void)(X)

typedef int (*handler)(char **str);

enum states
{
	WAIT_NUM,
	WAIT_OP,	
	ERROR
};

typedef struct transition
{
	enum states to;
	int (*handler)(char **str);
}trans_t;


static trans_t table[256][2];
static int g_is_initialized = 0;
static int NumHandler(char **str);
static int OpHandler(char **str);
static int ErrorHandler(char **str);
static int SpacesHandler(char **str);
static int UnaryHandler(char **str);
static int DivByZeroHandler(char **str);

void TransTableInit()
{
	int i = 0;
	
	for(; i < 256; ++i)
	{
		table[i][WAIT_NUM].to = ERROR;
		table[i][WAIT_NUM].handler = ErrorHandler;
		table[i][WAIT_OP].to = ERROR;
		table[i][WAIT_OP].handler = ErrorHandler;
	}
	
	for(i = '0'; i <= '9'; ++i)
	{
		table[i][WAIT_NUM].to = WAIT_OP;
		table[i][WAIT_NUM].handler = NumHandler;
	}	
	
	table['+'][WAIT_OP].to = WAIT_NUM;
	table['+'][WAIT_OP].handler = OpHandler;
	table['+'][WAIT_NUM].to = WAIT_OP;
	table['+'][WAIT_NUM].handler = UnaryHandler;
	
	
	table['-'][WAIT_OP].to = WAIT_NUM;
	table['-'][WAIT_OP].handler = OpHandler;
	table['-'][WAIT_NUM].to = WAIT_OP;
	table['-'][WAIT_NUM].handler = UnaryHandler;
	
	table['*'][WAIT_OP].to = WAIT_NUM;
	table['*'][WAIT_OP].handler = OpHandler;
	table['*'][WAIT_NUM].to = ERROR;
	table['*'][WAIT_NUM].handler = ErrorHandler;

	
	table['/'][WAIT_OP].to = WAIT_NUM;
	table['/'][WAIT_OP].handler = DivByZeroHandler;	
	table['/'][WAIT_NUM].to = ERROR;
	table['/'][WAIT_NUM].handler = ErrorHandler;
	
	table['^'][WAIT_OP].to = WAIT_NUM;
	table['^'][WAIT_OP].handler = OpHandler;	
	table['^'][WAIT_NUM].to = ERROR;
	table['^'][WAIT_NUM].handler = ErrorHandler;
	
	table[' '][WAIT_OP].to = WAIT_OP;
	table[' '][WAIT_OP].handler = SpacesHandler;	
	table[' '][WAIT_NUM].to = WAIT_NUM;
	table[' '][WAIT_NUM].handler = SpacesHandler;
		
	g_is_initialized = 1;		
} 

static int NumHandler(char **str)
{
    double ret = 0.0;
    ret = strtod(*str, str);
	AMPushNum(ret);

	return 0; 
}

static int OpHandler(char **str)
{
	enum status status;
	status = AMPushOp(**str);
	++*str;
	
	return status;	
}

static int SpacesHandler(char **str)
{
	++*str;

	return OK;
}

static int ErrorHandler(char **str)
{
	UNUSED(str);
	
	return E_SYNTAX;
}

static int UnaryHandler(char **str)
{
    double ret = 0.0;
    ret = strtod(*str, str);
	AMPushNum(ret);
	
	return 0;
}

static int DivByZeroHandler(char **str)
{
    if(*(*str+1) == '0')
    {
		return E_MATH;
	}

	return OpHandler(str);
}

int Calculate(char *str, double *result)
{
	char *runner = str;
	int status = 0;
	enum states curr_state = WAIT_NUM;
	trans_t transition_to;
	
	if(g_is_initialized == 0)
	{
		TransTableInit();
	}
	status = AMCreate(str);

	while('\0' != *runner && curr_state != ERROR)
	{			
		transition_to = table[(int)*runner][curr_state];	
		curr_state = transition_to.to;
		status = transition_to.handler(&runner);
	
		if(0 != status)
		{
			return status;
		}
	}
	
	*result = AMPushEOS();	
	AMDestroy();	
	
	return OK;			
}
