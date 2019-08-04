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

volatile int signalPid = -1;

void my_handler(int sig, siginfo_t *info, void *context);

int main()  
{
    printf("ping's pid: %d\n\n", getpid());
	struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = my_handler;

    sigaction(SIGUSR1, &sa, NULL);

	while(1)
	{
		pause();
		kill(signalPid, SIGUSR2);
	}
}

void my_handler(int sig, siginfo_t *info, void *context)
{
    signalPid = info->si_pid;

    printf("Ping\n");
    sleep(1);/* Just to make sure its working properly */
}