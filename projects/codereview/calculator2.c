/*************************************************************************************/
/* Calculator                                                                        */
/* Author- Inbar Namdar                                                              */
/* Reviewer - Daniel                                                                 */
/* Date - 07/07/2019                                                                 */
/*************************************************************************************/

#include <stdlib.h> /* size_t */
#include <string.h> /* strlen */

#include "calculator.h" /* Calculator header file */
#include "am.h" /* Arithmetic Module header file */

#define UNUSED(X) (void)(X)

/*enum status {OK, E_MATH, E_SYNTAX, E_MALLOC}; */

enum state {WAITING_NUM, WAITING_OP, ERROR};

typedef enum state state_t;

typedef int (*handler_f)(char **str, state_t next_state);

typedef struct transition
{
	state_t next_state;
	handler_f Handler;	
}transition_t;

void TTableInIt(transition_t **t_table);
static int ErrorHandler(char **str, state_t next_state);
static int OpHandler(char **str, state_t next_state);
static int NumHandler(char **str, state_t next_state);
static int ParenthesesHandler(char **str, state_t next_state);
static int SpaceHandler(char **str, state_t next_state);

state_t g_current_state = WAITING_NUM;

void TTableInit(transition_t t_table[256][3])
{
	int i = 0;
	
	for (i = '0' ; i <= '9'; ++i) 
	{
		t_table[i][WAITING_NUM].next_state = WAITING_OP;
		t_table[i][WAITING_NUM].Handler = NumHandler;
		t_table[i][WAITING_OP].next_state = ERROR;
		t_table[i][WAITING_OP].Handler = ErrorHandler;
	}
			
	for (i = '*'; i <= '/'; ++i) 
	{
		if (i != ',' && i != '.')
		{
			t_table[i][WAITING_NUM].next_state = ERROR;
			t_table[i][WAITING_NUM].Handler = ErrorHandler;
			t_table[i][WAITING_OP].next_state = WAITING_NUM;
			t_table[i][WAITING_OP].Handler = OpHandler;
		}
	}
	
	t_table['('][WAITING_NUM].next_state = WAITING_NUM;
	t_table['('][WAITING_NUM].Handler = ParenthesesHandler;
	t_table['('][WAITING_OP].next_state = ERROR;
	t_table['('][WAITING_OP].Handler = ErrorHandler;
	
	t_table[')'][WAITING_NUM].next_state = ERROR;
	t_table[')'][WAITING_NUM].Handler = ErrorHandler;
	t_table[')'][WAITING_OP].next_state = WAITING_OP;
	t_table[')'][WAITING_OP].Handler = ParenthesesHandler;
		
	t_table['^'][WAITING_NUM].next_state = ERROR;
	t_table['^'][WAITING_NUM].Handler = ErrorHandler;
	t_table['^'][WAITING_OP].next_state = WAITING_NUM;
	t_table['^'][WAITING_OP].Handler = OpHandler;
	
	t_table[' '][WAITING_NUM].next_state = WAITING_NUM;
	t_table[' '][WAITING_NUM].Handler = SpaceHandler;
	t_table[' '][WAITING_OP].next_state = WAITING_OP;
	t_table[' '][WAITING_OP].Handler = SpaceHandler;
}

static int NumHandler(char **str, state_t next_state)
{
	char *current_location;
	double num = strtod(*str, &current_location);
	
	*str = current_location;
	
	g_current_state = next_state;
	
	return PusnNum(num);
}

static int OpHandler(char **str, state_t next_state)
{
	char op = **str;
	
	++(*str);
	
	g_current_state = next_state;
	
	return PushOp(op);
}

static int SpaceHandler(char **str, state_t next_state)
{
	++(*str);
	
	g_current_state = next_state;
	
	return OK;
}

static int ErrorHandler(char **str, state_t next_state)
{
	UNUSED(str);
	g_current_state = next_state;
	
	return E_SYNTAX;
}

static int ParenthesesHandler(char **str, state_t next_state)
{
	char op = **str;
	
	++(*str);
	
	g_current_state = next_state;
	
	return Parentheses(op);
}

enum status Calculate(const char *str, double *result)
{
	static transition_t t_table[256][3] = {0};
	static int is_init = 0;
	char *runner = (char *)str;
	size_t len = strlen(str);
	enum status current_status = OK;
	
	if (!is_init)
	{
		TTableInit(t_table);
		
		is_init = 1;	
	}
	
	current_status = AMCreate(len);
	g_current_state = WAITING_NUM;
	
	while ('\0' != *runner && g_current_state != ERROR)
	{
		current_status = t_table[(int)*runner][g_current_state].Handler(&runner, 
								t_table[(int)*runner][g_current_state].next_state);	
	}			
	
	if (g_current_state != ERROR && current_status == OK)
	{
		current_status = EOS(result);							
	}
	
	AMDestroy();
	
	return current_status;
}
