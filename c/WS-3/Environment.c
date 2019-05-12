#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define UNUSED(x) (void)(x)

void copy(char *envp[]);
void PrintEnv(char *envp[]);

int main(int argc, char *argv[],char *envp[])
{
	UNUSED(argc);
	UNUSED(argv);
	copy(envp);
	
	return 0;
}

void PrintEnv(char *envp[])
{
	while(*envp != NULL)
	{	
			printf("%s\n",*envp);
			++envp;
	}

}

void copy(char *envp[])
{
	char **buffer;
	char **runner = envp;
	int charcounter = 0;
	int stringcounter = 0;
	
	while(NULL != *(runner + stringcounter))
	{
		++stringcounter;
	}
	
	buffer=(char**)malloc((stringcounter+1)*sizeof(char*));
	
	if(NULL == buffer)
	{
		free(buffer);
	}
	stringcounter=0;
	
	while(NULL != *(runner+stringcounter))
	{
		while('\0' != *(*(runner+stringcounter)+ charcounter))
		{
					++charcounter;
		}
		
		*(buffer+stringcounter)=(char*)malloc((charcounter+1)*sizeof(char));
		charcounter=0;
		++stringcounter;
	}
	stringcounter=0;
	
	/*runs on string array*/
	while(NULL != *(runner+stringcounter))
	{
		/*runs in char array*/
		while('\0' != *(*(runner+stringcounter)+charcounter))
		{
			(*(*(buffer+stringcounter)+charcounter)) = tolower((*(*(runner+stringcounter)+charcounter)));
			++charcounter;
		}
		
		*(*(buffer+stringcounter)+charcounter) = '\0';
		charcounter=0;
		++stringcounter;
	}
	
	*(buffer+stringcounter)=NULL;
	PrintEnv(buffer);
	stringcounter=0;
	while(NULL != *(buffer+stringcounter))
	{
		free(*(buffer+stringcounter));
		++stringcounter;
	}

	free(buffer);
}
