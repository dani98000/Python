#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define UNUSED(x) (void)(x)

void CreateBuffer(char **envp, char **buffer);
void CopyToLower(char *buffer, const char *envp);
void PrintBuffer(char *buffer[]);
void FreePointers(char **buffer);

int main(int argc, char *argv[],char *envp[])
{
	int count = 0;
	char **runner = envp;
	char **buffer = NULL;
	UNUSED(argc);
	UNUSED(argv);
	
	while(NULL != *runner)
	{
		++count;
		++runner;
	}
	buffer = (char**)malloc(sizeof(char *) * count + 1);
	
	if(NULL != buffer)
	{
		CreateBuffer(envp, buffer);
		PrintBuffer(buffer);
	}
	
	FreePointers(buffer);
	
	return 0;
}

void CreateBuffer(char **envp, char **buffer)
{
	int current_size = 0;
	char **env_runner = envp;
	char **buffer_runner = buffer;
	
	while(NULL != *env_runner)
	{
		current_size = strlen(*env_runner);
		*buffer_runner = (char *)malloc(sizeof(char) * current_size);
		
		if(*buffer_runner == NULL)
		{
			FreePointers(buffer);
			return;
		}
		
		CopyToLower(*buffer_runner, *env_runner);
		buffer_runner++;
		env_runner++;
	}
	
	buffer_runner = NULL;
}

void PrintBuffer(char *buffer[])
{
	while(*buffer != NULL)
	{	
			printf("%s\n",*buffer);
			++buffer;
	}

}

void CopyToLower(char *buffer, const char *envp)
{
	while('\0' != *envp)
	{
		*buffer = tolower(*envp);
		envp++;
		buffer++;
	} 
}

void FreePointers(char **buffer)
{
	char **buffer_runner = buffer;
	
	while(NULL != *buffer_runner)
	{
		free(*buffer_runner);
		++buffer_runner;
	}
	
	free(buffer);
}
