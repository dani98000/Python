#include <stdio.h>
#include <stdlib.h>/* malloc */
#include <sys/wait.h> /* wait */
#include <string.h>/* strtok */
#include <unistd.h>/* fork */

#define BUFFER 100
#define NUM_ARGS 20

int main()
{
    int pid = 0;
    char *input = NULL;
    int i = 0;

    char **argv = (char **)calloc(NUM_ARGS, sizeof(*argv));
    if(NULL == argv)
    {
        return -1;
    }

    input = malloc(BUFFER * sizeof(*input));
    if (!input)
    {        
        return -1;
    }  

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------WELCOME TO THE BEST SHELL YOU HAVE EVER SEEN-------------------------\n");
    printf("----------------------------------It’s not about how hard you can hit!----------------------------\n");
    printf("----------------------------------it’s about how hard you can get hit-----------------------------\n");
    printf("-----------------------------------------and keep moving forward.---------------------------------\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("--------------------------------------------Rocky Balboa, Rocky-----------------------------------\n");

    while(1)
    {
        i = 0;

        printf("$ ");

        if(!fgets(input, (BUFFER) * sizeof(*input), stdin))
        {
            break;
        }

        argv[i] = strtok(input,  " \n");
        do
        {
            ++i;
            argv[i] = strtok(NULL, " \n");
        }
        while(argv[i]);
        
        if(NULL == argv[0])
        {
            continue;
        }
        
        if (0 == strcmp("exit", argv[0]))
        {
            return 0;
        }

        pid = fork();            

        if(0 == pid)
        {               
            execvp(argv[0],argv);
            exit(0);
        }

        wait(NULL);
    }

    free(input);

    return 0;
}