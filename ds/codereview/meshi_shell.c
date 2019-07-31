/**********************
30/7/2019 Simple Shell
"exit" to exit 
**********************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <sys/types.h> /* fork, wait */
#include <sys/wait.h> /* wait */
#include <unistd.h> /* fork, execvp */
#include <string.h> /* strtok */
#include <errno.h> /* perror */

#define INPUT_LEN (100)
#define N_ARGS (20)

typedef enum bool
{
    FALSE = 0,
    TRUE = 1
} bool_t;

int Shell()
{
    const char *delim = " \n", *exit = "exit";
    char *input = NULL;
    char *args[N_ARGS] = {NULL};
    size_t i = 0LU;
    int status = 0;
    pid_t child_pid = 0;
    
    input = malloc(INPUT_LEN * sizeof(*input));
    if (!input)
    {
        perror("Alloc fail");
        
        return -1;
    }
    
    while (TRUE)
    {
        i = 0LU;
        printf("Meshi> ");
        input = fgets(input, (INPUT_LEN - 1) * sizeof(*input), stdin);
        if (!input)
        {
            perror("no input");
            
            return -1;
        }
       
        /* put args to array of strings */
        args[i++] = strtok(input, " \n");
        do 
        {
            args[i] = strtok(NULL, "\n");
        }
        while(args[i++]);
        
        if ('\n' == input[0])
        {
            continue;
        }
        
        if (0 == strcmp(exit, args[0]))
        {
            return 0;
        }
           
        if (!(child_pid = fork()))
        {
            status = execvp(args[0], args);
            
            return status;
        }
        
        wait(&status);
    }
    
    free(input);
    input = NULL;
    
    return 0;
}

int main()
{
    Shell();
}
