/********************************
*    Author: Daniel Maizel      *
*	      Date: 15/5/19         *
********************************/

#include <stdio.h> /*printf*/
#include <string.h> /*strspn*/
#include <strings.h> /*strcasecmp*/
#include <stdlib.h> /*exit*/

#define UNUSED(x) (void)(x)
 	
int AlwaysTrue(char UserInput[], char condition[]);
int Delete(char UserInput[], char *FileName);
int Exit();
int Count(char UserInput[], char *FileName);
int CompFunc(char UserInput[], char condition[]);
int DefaultAppend(char UserInput[], char *FileName);
int BeginningOfFile(char *UserInput, char *FileName);
int IsFirst(char UserInput[], char condition[]);
const struct item *ChainInit();
	
enum ERROR_LIST {OK = 1 , ERROR, EXIT}; 

struct item
{
    char *condition;
	int (*cfp)(char UserInput[], char condition[]);
	int (*ofp)(char UserInput[], char *FileName);
};

int main(int argc, char *argv[])
{
	int i = 0, d = 0;
	int flag = 0;
	int res = 0; 
	char *FileName;
	char UserInput[100];
	const struct item *Chain = ChainInit();
	FileName = argv[1];
	UNUSED(argc);
	UNUSED(d);
	
	while(!flag)
	{
		fgets(UserInput, 8, stdin);
		
		for(i = 0; i < 5; ++i)
		{
			if(Chain[i].cfp(UserInput, Chain[i].condition))
			{	
				d = Chain[i].cfp(UserInput, Chain[i].condition);
				res = Chain[i].ofp(UserInput, FileName);
				if(res == EXIT)
				{
					flag = 1;
					break;
				}
				if(res == ERROR)
				{
					printf("Error Occured");
					break;
				}
				break;
			}
		}
		i = 0;
	}
	
	return 0;
}
	

int CompFunc(char UserInput[], char condition[])
{
	return(0 == strcasecmp(UserInput,condition));
} 

int IsFirst(char UserInput[], char condition[])
{
	UNUSED(condition);
	
	return(strspn(UserInput, condition) == 1);
} 


int AlwaysTrue(char UserInput[], char condition[])
{
	UNUSED(UserInput);
	UNUSED(condition);
	
	return OK;
}

int Count(char *UserInput, char *FileName)
{
	int lines = 0;
	char ch;
	FILE *fPtr = fopen(FileName , "r+");
	UNUSED(UserInput);
	
	if(NULL == fPtr)
    {
		fPtr = fopen(FileName , "w+");
    }
 
	while((ch = fgetc(fPtr)) != EOF)
	{
	    if('\n' == ch)
	    {
	    	++lines;
	    }
	}
	

    fprintf(fPtr, "%d\n", lines);
    fclose(fPtr);
    
    return 0;
}

int Exit()
{
	printf("Program Closed");
	
	return EXIT;
}

int Delete(char UserInput[], char *FileName)
{
	int ret = remove(FileName);
	UNUSED(UserInput);

    if(0 == ret) 
    {
    	printf("File deleted successfully\n");
    	
    	return EXIT;
    }
    
	return 0;
}

int DefaultAppend(char *UserInput, char *FileName)
{
	FILE *fPtr = fopen(FileName, "a");
	int i = 0;
	
	if(NULL == fPtr)
    {
        printf("Unable to create file.\n");
        
        return EXIT;
    }
    
    while('\0' != UserInput[i])
    {
		putc(UserInput[i], fPtr);
		++i;
	}
	fclose(fPtr);
	
	return OK;
}

int BeginningOfFile(char *UserInput, char *FileName)
{
	FILE *temp = fopen("temp.txt", "w+");
	FILE *fPtr = fopen(FileName, "r+");
	char c, d;
	
	if(NULL == fPtr)
    {
    	fPtr = fopen(FileName, "w+");
    }
    if(NULL == temp)
    {
        printf("Unable to create file.\n");
        
		return ERROR;
    }
	c = fgetc(fPtr);
	
	while(c != EOF) 
    { 
        fputc(c, temp); 
        c = fgetc(fPtr); 
    }  
    
   	rewind(fPtr);
   	rewind(temp);
    fprintf(fPtr, "%s", UserInput + 1);
	d = fgetc(temp);
	
	while (d != EOF) 
    { 
        fputc(d, fPtr); 
        d = fgetc(temp); 
    }  
    
	fclose(fPtr);
	fclose(temp);
	remove("temp.txt");
	
	return OK;
}

const struct item *ChainInit()
{
	static const struct item Chain[5]= 
	{    
   		{"-count\n", CompFunc, Count},
    	{"-remove", CompFunc, Delete},
   		{"-exit\n", CompFunc, Exit},
    	{"<", IsFirst, BeginningOfFile},
    	{" ", AlwaysTrue, DefaultAppend}
	};
	
	return (Chain); 
}
