#include <stdio.h> /* printf */
#include <sys/types.h> /*fork*/
#include <unistd.h> /*fork*/
#include <stdlib.h> /* exit */
#include <signal.h> /* signal */
#include <wait.h>

void handler1(int signum);
void handler2(int signum);

void handler1(int signum)
{
	write(1,"Ping!\n", 7);
	sleep(1);
}

int main()
{
	struct sigaction action;
	action.sa_handler = handler1;
	sigaction(SIGUSR1, &action, NULL);
	char *args[] = {"./child.out", NULL};

	pid_t child_pid = fork();

	

	if(!child_pid)
	{
		execv(args[0], args);
	}
	else
	{
		wait(NULL);
		sleep(1);

		while(1)
		{
			/*printf("parent process\n");*/
			kill(child_pid, SIGUSR2);
			pause();
		}
	}
	

	return 0;
}
