/********************************
*	Author: Eran Segal			*
*	Reviewer: Danil Mazil	 	*
*	Date: 4/8/19				*
********************************/

#include <signal.h> /* sigaction */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* sleep */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* atoi */

#define UNUSED(X) ((void)(X))

volatile sig_atomic_t g_sig_flag; 

void SigHandler(int signum)
{
	(void)(signum);
	g_sig_flag = 1;	
}

int main(int argc, char const *argv[])
{
	pid_t pid = atoi(argv[1]);
	struct sigaction sa;
	
	UNUSED(argc);
	sa.sa_handler = SigHandler;
	sigaction(SIGUSR1, &sa, NULL);

	while (1)
    {
        if (g_sig_flag)
        {
            g_sig_flag = 0;
            write(STDOUT_FILENO, "Pong\n", 6);
            sleep(1);
            kill(pid, SIGUSR1);
        }
        sleep(1);
    }

	return 0;
}