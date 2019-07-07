#include <math.h> /* pow */
#include <stdio.h> /* printf */

#include "am.h" /* Arithmetic Module header file */
#include "../../ds/include/stack.h" /* Stack header file */

typedef double (*handler_f)(double num1, double num2);

enum associativity {LR, RL};

typedef struct operator
{
	int precedence;
	enum associativity associativity;
	handler_f Handler;
}operator_t;

static operator_t op_table[256];
stack_t *num_stack;
stack_t *op_stack;
static enum status g_current_status = OK;

static void OPTableInit(operator_t op_table[256]);
static double Division(double num1, double num2);
static double Subtraction(double num1, double num2);
static double Addition(double num1, double num2);
static double Multiplication(double num1, double num2);
static double Power(double num1, double num2);

static void OPTableInit(operator_t op_table[256])
{
	op_table['*'].Handler = Multiplication;
	op_table['+'].Handler = Addition;	
	op_table['-'].Handler = Subtraction;
	op_table['/'].Handler = Division;
	op_table['^'].Handler = Power;
	op_table['('].Handler = NULL;
	op_table[')'].Handler = NULL;
	op_table['@'].Handler = Division;
	
	op_table['*'].precedence = 3;
	op_table['+'].precedence = 4;	
	op_table['-'].precedence = 4;
	op_table['/'].precedence = 3;
	op_table['^'].precedence = 2;
	op_table['('].precedence = 9;
	op_table[')'].precedence = 9;
	op_table['@'].precedence = 10;
	
	op_table['*'].associativity = LR;
	op_table['+'].associativity = LR;	
	op_table['-'].associativity = LR;
	op_table['/'].associativity = LR;
	op_table['^'].associativity = RL;
	op_table['('].associativity = RL;
	op_table[')'].associativity = RL;
	op_table['@'].associativity = LR;
	
}

static double Multiplication(double num1, double num2)
{
	return num1 * num2;
}

static double Addition(double num1, double num2)
{
	return num1 + num2;
}

static double Subtraction(double num1, double num2)
{
	return num1 - num2;
}

static double Division(double num1, double num2)
{
	if(0 == num2)
	{
		g_current_status = E_MATH;
		
		return 0;
	}
	else
	{
		return num1 / num2;
	}
}

static double Power(double num1, double num2)
{
	return pow(num1, num2);
}

static void Calc()
{
	double first_num = 0;
	double second_num = 0;
	char op = '0';
	double result = 0;
	
	second_num = *(double *)STACKPeek(num_stack);
	STACKPop(num_stack);
	first_num = *(double *)STACKPeek(num_stack);
	STACKPop(num_stack);
	op = *(char *)STACKPeek(op_stack);
	STACKPop(op_stack);
	result = op_table[(int)op].Handler(first_num, second_num);
	STACKPush(num_stack, &result);
}

enum status AMCreate(size_t len)
{
	char stab = '@';
	num_stack = STACKCreate(len, sizeof(double));
	if (NULL == num_stack)
	{
		return E_MALLOC;
	}
	
	op_stack = STACKCreate(len, sizeof(char));
	if (NULL == op_stack)
	{
		free(num_stack);
		
		return E_MALLOC;
	}
	
	OPTableInit(op_table);
	g_current_status = OK;
	
	STACKPush(op_stack, &stab);
	
	return OK;
}

void AMDestroy()
{
	STACKDestroy(num_stack);
	STACKDestroy(op_stack);
}

enum status PushOp(char new_op)
{
	char last_op = *(char *)STACKPeek(op_stack);
	
	if ('(' == new_op)
	{
		STACKPush(op_stack, &new_op);
		
		return g_current_status;
	}
	
	while (op_table[(int)new_op].precedence > op_table[(int)last_op].precedence)
	{
		Calc();
		last_op = *(char *)STACKPeek(op_stack);
	}
	
	while (op_table[(int)new_op].precedence == op_table[(int)last_op].precedence 
									&& op_table[(int)last_op].associativity == LR)
	{
		Calc();
		last_op = *(char *)STACKPeek(op_stack);
	}
	
	if (g_current_status == OK)
	{
		STACKPush(op_stack, &new_op);
	}
	
	return g_current_status;
}

enum status PusnNum(double num)
{
	double number = num;
	
	STACKPush(num_stack, &number);
	
	return OK;
}

enum status Parentheses()
{
	while (1 < STACKSize(num_stack) && '(' != *(char *)STACKPeek(op_stack))
	{
		Calc();
	}
	
	STACKPop(op_stack);
	
	return g_current_status;
}

enum status EOS(double *result)
{
	while (1 < STACKSize(num_stack))
	{
		Calc();
	}
	*result = *(double *)STACKPeek(num_stack);
	
	if('(' == *(char *)STACKPeek(op_stack))
	{
		g_current_status = E_SYNTAX;
	}
		
	return g_current_status;
}
