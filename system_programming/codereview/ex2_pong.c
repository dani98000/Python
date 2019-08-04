/********************************
*	Author: Eran Segal			*
*	Reviewer: Danil Mazil	 	*
*	Date: 4/8/19				*
********************************/

#include <stdio.h> /* perror */
#include <signal.h> /* sigaction */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* getppid */
#include <stdlib.h> /* exit */
#include <errno.h>	/* perror */

volatile sig_atomic_t g_sig_flag = 1;

void SigHandler(int signum)
{
	(void)(signum);
	g_sig_flag = 1;	
}

void ChildPing()
{
    
    
    pid_t ppid = getppid();
	struct sigaction pong_act;
    pong_act.sa_handler = SigHandler;
    if (0 > sigaction(SIGUSR1, &pong_act, NULL))
	{
		perror("sigaction");
		exit(1);
	}

    printf("\n child: pid(%d), ppid(%d) ",getpid(), getppid());

    printf("\n 2");
    sleep(1);
    printf("\n 1\n");
    sleep(1);

    while (ppid == getppid())
    {
        if (g_sig_flag)
        {
            g_sig_flag = 0;
            write(STDOUT_FILENO, "Child: Ping\n", 13);
            sleep(1);
            kill(ppid, SIGUSR2);
        }
        sleep(1);
    }
}

int main()
{
    ChildPing();

    return 0;
}