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
	char **runner=envp;
	int charcounter=0;
	int stringcounter=0;
	while(*(runner+stringcounter) != NULL)
	{
		++stringcounter;
	}
	buffer=(char**)malloc((stringcounter+1)*sizeof(char*));
	assert(buffer != NULL);
	stringcounter=0;
	while(*(runner+stringcounter) != NULL)
	{
		while(*(*(runner+stringcounter)+ charcounter) != '\0')
		{
					++charcounter;
		}
		*(buffer+stringcounter)=(char*)malloc((charcounter+1)*sizeof(char));
		charcounter=0;
		++stringcounter;
	}
	stringcounter=0;
	
	/*runs on string array*/
	while(*(runner+stringcounter) != NULL)
	{
		/*runs in char array*/
		while(*(*(runner+stringcounter)+charcounter) != '\0')
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
	while(*(buffer+stringcounter) != NULL)
	{
		free(*(buffer+stringcounter));
		++stringcounter;
	}
	free(buffer);
}
