#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>
  
void my_handler2(int signum);
void my_handler(int signum);
  
int main() 
{ 
    pid_t pid;
    pid_t parent_pid = getpid(); 
  
    /* get child process */
    if ((pid = fork()) < 0) { 
        perror("fork"); 
        exit(1); 
    } 
  
    if (pid == 0) { /* child */

		signal(SIGUSR1, my_handler);
		printf("\nChild %d: sending SIGUSR2 to parent %d\n\n", getpid(), getppid()); 
    	while(1)
    	{
			kill(getppid(), SIGUSR2);
	    	pause();
    	}
    }
    else /* parent */
    {
		signal(SIGUSR2, my_handler2);

    	pause();

        printf("\nPARENT %d: sending SIGUSR1\n\n", getpid()); 
        while(1)
        {
        	kill(pid, SIGUSR1);
        	pause();
 	    }    
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

void my_handler2(int signum)
{
    if (signum == SIGUSR2)
    {
        printf("I am parent [%d] and i Received SIGUSR2!\n", getpid());
    }
    sleep(1);
}

