#include <string.h>
#include <stdio.h>

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


