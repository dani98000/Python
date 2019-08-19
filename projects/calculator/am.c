#include <string.h> /* strlen */
#include <math.h> /* pow */
#include <assert.h> /* assert */

#include "am.h" /* am header file */
#include "parser.h" /* parser header file */
#include "../ds/include/stack.h" /* stack header file */

enum precedence
{
	DOLLAR = 10,
	CLOSINGPAR = 6,
	OPENPAR = 5,
	ADD = 4,
	SUB = 4,
	MULT = 3,
	DIV = 3,
	POW = 2
};

enum associativity
{
	LEFT_TO_RIGHT,
	RIGHT_TO_LEFT
};

typedef struct operator
{
	enum associativity associativity;
	enum precedence precedence;
	handler_func handler;
}operator_t;

static int go_is_initialized = 0;
static stack_t *num_stack;
static stack_t *op_stack;

static operator_t table[256];
static int PowHandler(double num1, double num2);
static int SubHandler(double num1, double num2);
static int DivHandler(double num1, double num2);
static int AddHandler(double num1, double num2);
static int MultHandler(double num1, double num2);

int AMCreate(char *str)
{
	size_t stack_size = 0;
	char stub = '$';	
	
	assert(NULL != str);
	
	stack_size = strlen(str);
	
	num_stack = STACKCreate(stack_size, sizeof(double));
	if(NULL == num_stack)
	{
		return E_MALLOC;
	}
	
	op_stack = STACKCreate(stack_size, sizeof(char));
	if(NULL == num_stack)
	{
		STACKDestroy(num_stack);
		
		return E_MALLOC;
	}
	
	STACKPush(op_stack, (void *)&stub);
	
	if(go_is_initialized == 0)
	{
		OpTableInit();
	}	
	
	return OK;

}

void OpTableInit()
{
	int i = 0;
	
	for(; i < 256; ++i)
	{
		if(i == '+')
		{
			table[i].associativity = LEFT_TO_RIGHT;
			table[i].precedence = ADD;
			table[i].handler = AddHandler;
		}
		else if(i == '-')
		{
			table[i].associativity = LEFT_TO_RIGHT;
			table[i].precedence = SUB;
			table[i].handler = SubHandler;
		}	
	
		else if(i == '*')
		{
			table[i].associativity = LEFT_TO_RIGHT;
			table[i].precedence = MULT;
			table[i].handler = MultHandler;
		}
		else if(i == '/')
		{
			table[i].associativity = LEFT_TO_RIGHT;
			table[i].precedence = DIV;
			table[i].handler = DivHandler;		
		}
		else if(i == '^')
		{
			table[i].associativity = RIGHT_TO_LEFT;
			table[i].precedence = POW;
			table[i].handler = PowHandler;		
		}

		else if(i == '$')
		{
			table[i].associativity = RIGHT_TO_LEFT;
			table[i].precedence = DOLLAR;
			table[i].handler = NULL;
		}
		else if(i == '(')
		{
			table[i].associativity = LEFT_TO_RIGHT;
			table[i].precedence = OPENPAR;
			table[i].handler = NULL;		
		}

		else if(i == ')')
		{
			table[i].associativity = RIGHT_TO_LEFT;
			table[i].precedence = CLOSINGPAR;
			table[i].handler = AMPushClosing;
		}
	}
			
	go_is_initialized = 1;		
}

void AMDestroy()
{
	STACKDestroy(num_stack);
	STACKDestroy(op_stack);
}

void AMPushNum(double num)
{
	STACKPush(num_stack, (void *)&num);
}

int AMPushOp(char op)
{
	double num1 = 0.0;
	double num2 = 0.0;
	
	operator_t current;
	operator_t prev;
	enum status status = OK ;
	
	current = table[(int)op];
	prev = (table[(int)*(char *)STACKPeek(op_stack)]);
	
	if(current.associativity == LEFT_TO_RIGHT)
	{
		while(prev.precedence <= current.precedence && (int)op != '(')
		{
			num2 = 	*(double *)STACKPeek(num_stack);
			STACKPop(num_stack);
			num1 = *(double *)STACKPeek(num_stack);
			STACKPop(num_stack);
	
			STACKPop(op_stack);
		
			status = prev.handler(num1, num2);
			if(OK != status)
			{
				return status;
			}
			
			prev = (table[(int)*(char *)STACKPeek(op_stack)]);
		}
	}
	
	else
	{
		while(prev.precedence < current.precedence)
		{
			num2 = 	*(double *)STACKPeek(num_stack);
			STACKPop(num_stack);
			num1 = *(double *)STACKPeek(num_stack);
			STACKPop(num_stack);

			STACKPop(op_stack);

			status = prev.handler(num1, num2);
			if(OK != status)
			{
				return status;
			}

			prev = table[(int)*(char *)STACKPeek(op_stack)];
			
			if((int)*(char *)STACKPeek(op_stack) == '(')
			{
				break;
			}
		}
	}
	
	STACKPush(op_stack, (void *)&op);
			
	return status;
}

static int AddHandler(double num1, double num2)
{
	double result = num1 + num2;
	STACKPush(num_stack, (void *)&result);
	
	return 0;
}
static int MultHandler(double num1, double num2)
{
	double result = num1 * num2;
	STACKPush(num_stack, (void *)&result);
	
	return 0;
}

static int DivHandler(double num1, double num2)
{
	double result = 0;
	
	if((int)num2 == 0)
	{
		return E_MATH;
	}
	
	result = num1 / num2;
	STACKPush(num_stack, (void *)&result);
	
	return OK;
}

static int SubHandler(double num1, double num2)
{
	double result = num1 - num2;
	STACKPush(num_stack, (void *)&result);
	
	return 0;
}

static int PowHandler(double num1, double num2)
{
	double result = pow(num1, num2);
	STACKPush(num_stack, (void *)&result);
	
	return 0;
}

int AMPushEOS(double *result)
{	
	enum status status = OK;
	status = AMPushOp('$');
	
	assert(NULL != result);	
	
	if(STACKSize(op_stack) > 2)
	{
		return E_SYNTAX;
	}
	
	if(status == OK)
	{
		*result = *(double *)STACKPeek(num_stack);	
	}
	
	
	return status;
}

int AMPushClosing()
{
	AMPushOp(')');
	STACKPop(op_stack);
	
	if('(' ==  *(char *)STACKPeek(op_stack))
	{
			STACKPop(op_stack);
			return OK;
	}
	
	return E_SYNTAX;
}
