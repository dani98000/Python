typedef struct transition
{
	states to;
	int (*handler)(char *str);
}trans_t

enum states
{
	W.N;
	W.O;
	ERROR;
}

int next_state = W.N;

static int NumHandler(char *str, int next_state);
static int OpHandler(char *str, int next_state);

trans_t *TransTableInit()
{
	int i = 0;

	trans_t *table[256][2];
	
	for(; i < 256; ++i)
	{
		table[i][W.N]->to = ERROR;
		table[i][W.N]->hanlder = ErrorFunc;
		table[i][W.O]->to = ERROR;
		table[i][W.O]->hanlder = ErrorFunc;
	}
	
	for(i = '0'; i <= '9'; ++i)
	{
		table[i][W.N]->to = W.O;
		table[i][W.N]->hanlder = NumHandler;
	}	
	
	table['+'][W.O]->to = W.N;
	table['+'][W.O]->handler = OpHandler;
	
	table['-'][W.O]->to = W.N;
	table['-'][W.O]->handler = OpHandler;
	
	table['*'][W.O]->to = W.N;
	table['*'][W.O]->handler = OpHandler;
	
	table['/'][W.O]->to = W.N;
	table['/'][W.O]->handler = OpHandler;	
	
	table['\0'][W.O]->to = W.N;
	table['\0'][W.O]->handler = OpHandler;		
} 

static int NumHandler(char *str, int next_state)
{
	char *ptr = NULL;
    double ret = NULL;
    ret = strtod(str, &str);
    next_state = W.O;

	return PushNum(ret);
}

static int OpHandler(char *str, int next_state)
{
	next_state = W.N;		
	return PushOp(*str);
}

int Calculate(const char *str, dobule result)
{
	char *runner = str;
	double num = 0.0;
	
	while(NULL != *runner && state != ERROR)
	{
				
	}
}
