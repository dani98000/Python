#include <signal.h> /* sigaction */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* sleep */
#include <sys/types.h> /* wait */
#include <sys/wait.h>


void my_handler(int signum);

int main(int argc, char *argv[])  
{
	struct sigaction action;
	int pid;
	action.sa_handler = my_handler;
    sigaction(SIGUSR2, &action, NULL);

	pid = atoi(argv[1]);
	printf("%d\n\n", pid);

	printf("hello world\n\n");

	while(1)
	{
		kill(pid, SIGUSR1);
		pause();
	}
}

void my_handler(int signum)
{
        printf("Pong\n");
        sleep(1);
}