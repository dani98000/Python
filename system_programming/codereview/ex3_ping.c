/********************************
*	Author: Eran Segal			*
*	Reviewer: Danil Mazil	 	*
*	Date: 4/8/19				*
********************************/

#include <signal.h> /* sigaction */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* sleep */
#include <unistd.h> /* sleep */

#define UNUSED(X) ((void)(X))

volatile sig_atomic_t g_sig_flag; 
volatile pid_t g_sender_pid;

void SigHandler(int signum, siginfo_t *info, void *context)
{
	UNUSED(context);
    UNUSED(signum);

    g_sender_pid = info->si_pid;
	g_sig_flag = 1;
}

int main()
{
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = SigHandler;
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
	{
		pause();

		if (g_sig_flag)
		{
			g_sig_flag = 0;
			write(STDOUT_FILENO, "Ping\n", 6);
			sleep(1);
		    kill(g_sender_pid, SIGUSR2);
		}
	}

	return 0;
}

