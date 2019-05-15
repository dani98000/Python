/********************************
*    Author: Daniel Maizel      *
*	      Date: 15/5/19         *
********************************/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)
#define DATA_SIZE 1000
 	
int AlwaysTrue(char UserInput[],char condition[]);
int Delete(char UserInput[], char *FileName);
int Exit();
int Count(char UserInput[], char *FileName);
int CompFunc(char UserInput[], char condition[]);
int DefaultAppend(char UserInput[], char *FileName);
int BeginningOfFile(char *UserInput, char *FileName);
int IsFirst(char UserInput[],char condition[]);
	


struct item
{
    char condition[DATA_SIZE];
	int (*cfp)(char UserInput[],char condition[]);
	int (*ofp)(char UserInput[],char *FileName);
} 
Chain[5]= 
{    
   	{"-count\n", CompFunc, Count},
    {"-remove", CompFunc, Delete},
   	{"-exit\n", CompFunc, Exit},
    {"i", AlwaysTrue, DefaultAppend},
    {"<", IsFirst, BeginningOfFile}
};


int main(int argc, char *argv[])
{

	int i;
	int flag =0;
	int res = 0; 
	int d;
	char *FileName;
	char UserInput[100];
	FileName = argv[1];
	UNUSED(argc);
	UNUSED(d);
	
			
	while(!flag)
	{
	fgets(UserInput, 8, stdin);
		
		for(i = 0; i < 5; i++)
		{
			if(Chain[i].cfp(UserInput, Chain[i].condition))
			{	
				d=Chain[i].cfp(UserInput, Chain[i].condition);
				res = Chain[i].ofp(UserInput, FileName);
				if(res == 4)
				{
					flag = 1;
					break;
				}
				break;
			}
		}
		i=0;
	}
	
	return 0;
}
	

int CompFunc(char UserInput[],char condition[])
{
	return(strcasecmp(UserInput,condition) == 0);
} 

int IsFirst(char UserInput[],char condition[])
{
	return(strspn(UserInput,"<") == 1);
} 


int AlwaysTrue(char UserInput[],char condition[])
{
	UNUSED(UserInput);
	UNUSED(condition);
	return 1;
}

int Count(char *UserInput, char *FileName)
{
	int lines=0;
	FILE *fPtr = fopen(FileName , "r+");
	char ch;
	UNUSED(UserInput);
	while((ch=fgetc(fPtr))!=EOF)
	{
	    if(ch == '\n')
	    {
	    	++lines;
	    }
	}
	

    fprintf(fPtr,"%d\n",lines);
    fclose(fPtr);
    return 0;
}

int Exit()
{
	printf("Exit");
	exit(0);
	return 4;
}

int Delete(char UserInput[], char *FileName)
{
	int ret = remove(FileName);
	UNUSED(UserInput);

    if(ret == 0) 
    {
    	printf("File deleted successfully\n");
    	exit(0);
    }
    else 
    {
  	  printf("Error: unable to delete the file\n");
    }
   
	return(0);
}

int DefaultAppend(char *UserInput, char *FileName)
{
	FILE *fPtr = fopen(FileName, "a");
	int i = 0;
	
	if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        exit(0);
    }
    
    while(UserInput[i] != '\0')
    {
		putc(UserInput[i], fPtr);
		++i;
	}
	
	fclose(fPtr);
	return 1;
}

int BeginningOfFile(char *UserInput, char *FileName)
{
	FILE *temp = fopen("temp.txt", "r+");
	FILE *fPtr = fopen(FileName, "r+");
	char c,d;
	if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        exit(0);
    }
	c = fgetc(fPtr);
	while (c != EOF) 
    { 
        fputc(c, temp); 
        c = fgetc(fPtr); 
    }  
   	rewind(fPtr);
   	rewind(temp);

    fprintf(fPtr,"%s",UserInput);
    
	d = fgetc(temp);
	while (d != EOF) 
    { 
        fputc(d, fPtr); 
        d = fgetc(temp); 
    }  
    
	fclose(fPtr);
	fclose(temp);
	remove("temp.txt");
	return 1;
}
