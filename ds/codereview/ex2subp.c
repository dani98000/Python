#include <stdio.h> /* printf */
#include <sys/types.h> /*fork*/
#include <unistd.h> /*fork*/
#include <stdlib.h> /* exit */
#include <signal.h> /* signal */
#include <wait.h>

void handler2(int signum)
{
    write(1,"Pong!\n", 7);
    sleep(1);
}

int main()
{
	struct sigaction action;
	action.sa_handler = handler2;
	sigaction(SIGUSR2, &action, NULL);

	while(1)
	{
		/*printf("child process\n");*/
		kill(getppid(), SIGUSR1);
		pause();

	}

	return 0;
}