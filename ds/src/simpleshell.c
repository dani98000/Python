#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#include <limits.h>

#define BUFFER 100

char **get_input(char *input) 
{
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}

int main(int argc, char **argv)
{
    char line[BUFFER];
    char program[20];
    char command[50];
    char cwd[50];
    char* path = "/bin/"/*getcwd(cwd, sizeof(cwd))*/;
    int pid = 0;

    while(1)
    {
        printf("$ ");

        if(!fgets(line, BUFFER, stdin))
        {
            break;
        }

        memset(command,0,sizeof(command));
        memset(program,0,sizeof(program));
    

        if(strncmp(line, "exit", (strlen(line)-1))==0)
        {
            break;
        }

        strncpy(command,line,(strlen(line)-1));
        strcpy(program, path);
        strcat(program,command);

        printf("command: %s\n", command);
        printf("line: %s\n", line);
        printf("program: %s\n", program); 

        pid = fork();            

        if(0 == pid)
        {               
            execl(program,command,NULL);
            exit(0);
        }
    }

    return 0;
}