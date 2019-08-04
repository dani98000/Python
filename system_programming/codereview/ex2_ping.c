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

volatile sig_atomic_t g_sig_flag = 0;

static void SigHandler(int signum)
{
	(void)(signum);
	g_sig_flag = 1;	
}

void ParentPong()
{
    char *argv[] = {"./a.out", NULL};
	
    pid_t pid = 0;
    struct sigaction ping_act;
    ping_act.sa_handler = SigHandler;
    if (0 > sigaction(SIGUSR2, &ping_act, NULL))
	{
		perror("sigaction");
		exit(1);
	}

    printf("\n parent: pid(%d) ",getpid());
    printf("\n fork in 3");
    sleep(1);
    printf("\n fork in 2");
    sleep(1);
    printf("\n fork in 1\n");
    sleep(1);

    pid = fork();
    if (!pid)
    {
        if (execvp(argv[0], argv))
        {
            perror("execv");
        }
    }

    while (1)
    {
        if (g_sig_flag)
        {
            g_sig_flag = 0;
            write(STDOUT_FILENO, "Parent: Pong\n", 14);
            sleep(1);
            kill(pid, SIGUSR1);
        }
        sleep(1);
    }
}

int main()
{
    ParentPong();

    return 0;
}