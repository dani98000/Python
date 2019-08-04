/********************************
*    Author  : Daniel Maizel    *
*    Date    : 01/08/2019       *
*    Reviewer: Sandra           *
*                               *
*********************************/
#include <signal.h> /* sigaction */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* sleep */
#include <sys/types.h> /* wait */
  
void my_handler2(int signum);
void my_handler(int signum);

int main() 
{ 
    pid_t pid;
    struct sigaction action;

	action.sa_handler = my_handler;
    sigaction(SIGUSR1, &action, NULL);	
	action.sa_handler = my_handler2;
    sigaction(SIGUSR2, &action, NULL);

    action.sa_flags = 0;
  	
    /* get child process */
    if ((pid = fork()) < 0) 
    { 
        perror("fork"); 
        exit(1); 
    } 
    
    if (pid == 0) 
    { /* child */
    	printf("\nChild %d: sending SIGUSR2 to parent %d\n\n", getpid(), getppid()); 

    	while(1)
    	{
			kill(getppid(), SIGUSR2);
	    	pause();
    	}
    }
    else /* parent */
    {
    	/*wait(NULL);*/
        
        printf("\nPARENT %d: sending SIGUSR1 to child %d\n\n", getpid(), pid); 
        
        while(1)
        {
        	kill(pid, SIGUSR1);
        	pause();
 	    }    
    }

    return 0; 
} 

void my_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        printf("I am child [%d] and i Received SIGUSR1!\n", getpid());
        sleep(1);
    }
}

void my_handler2(int signum)
{
    if (signum == SIGUSR2)
    {
        printf("I am parent [%d] and i Received SIGUSR2!\n", getpid());
        sleep(1);
    }
}

