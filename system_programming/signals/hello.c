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
#include <sys/wait.h>

void my_handler(int signum);

int main()
{
	struct sigaction action;
	action.sa_handler = my_handler;
    sigaction(SIGUSR1, &action, NULL);	

	printf("\nChild %d: sending SIGUSR2 to parent %d\n\n", getpid(), getppid()); 

    while(1)
    {
		kill(getppid(), SIGUSR2);
	   	pause();
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