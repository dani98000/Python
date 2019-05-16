#include <string.h>
#include <stdio.h>

#define RUN_TEST(test)\
if(!test())\
{\
printf(#test " - failed!\n");\
}\
else\
{\
printf(#test " - ok!\n");\
}

char *strtok1(char *str, const char *delim)
{
	static char *current_start = NULL;
    char *runner = current_start;
    char *cleaner = runner;
    static char *original_end = NULL;
    
	if(NULL != str)
	{
		current_start = str;
		original_end=str+strlen(str);
		runner=current_start;
		cleaner=runner;
	}
	 
	if(NULL == str && NULL == current_start)
	{
		return(NULL);
	}


	runner += strspn(current_start, delim);
	if(runner < original_end)
	{
		while(cleaner < runner)
		{
			*cleaner = '\0';
			++cleaner;
		}
		
		cleaner += strcspn(runner, delim);
		current_start = cleaner + strspn(cleaner, delim);
		
		while(cleaner != current_start)
		{
			*cleaner = '\0';
			++cleaner;
		}
	}
	else
	{
		return(NULL);
	}
	
	return(runner);
}

int test_strtok()
{
	char str[] = "||db:c";
	char str2[]="||";
	const char s[] = "|:;";
	char *token,*token2;
   
    token = strtok1(str, s);
    token2 = strtok1(str2, s);
   
	return(str[2] == *token && NULL == token2);
}

int main()
{
	RUN_TEST(test_strtok);
	return 0;
}
