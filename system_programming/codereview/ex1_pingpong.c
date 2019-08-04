/********************************
*	Author: Eran Segal			*
*	Reviewer: Danil Maizel	 	*
*	Date: 4/8/19				*
********************************/

#include <stdio.h> /* perror */
#include <signal.h> /* sigaction */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* getppid */
#include <stdlib.h> /* exit */
#include <errno.h>	/* perror */

volatile sig_atomic_t g_sig_flag = 0;

void SigHandler(int signum)
{
	(void)(signum);
	g_sig_flag = 1;	
}

void SignalPingPong()
{
	pid_t pid = 0;
	struct sigaction sigact1;
	struct sigaction sigact2;

	sigact1.sa_handler = &SigHandler;
	sigact2.sa_handler = &SigHandler;	
	if (0 > sigaction(SIGUSR1, &sigact1, NULL) || 0 > sigaction(SIGUSR2, &sigact2, NULL))
	{
		perror("sigaction");
		exit(1);
	}

	pid = fork();

	if (pid)
	{
		raise(SIGUSR2);
	}

	while (1)
	{
		if (g_sig_flag)			
		{
			g_sig_flag = 0;

			if (pid)	/* parent */
			{
				write(STDOUT_FILENO, "\n Parent: Ping", 15);
/*				sleep(1);*/
				kill(pid, SIGUSR1);
			}
			else		/* child */
			{
				write(STDOUT_FILENO, "\n Child: Pong", 14);
/*				sleep(1);
*/				kill(getppid(), SIGUSR2);	
			}
		}
		/*sleep(1);*/
	}
}

int main()
{
	SignalPingPong();

	return 0;
}
