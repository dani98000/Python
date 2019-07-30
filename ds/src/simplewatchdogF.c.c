#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
int main() 
{
	int i = 0;

	sleep(1);

	for(i = 0; i < 10; ++i) 
    { 
        if(fork() == 0) 
        { 
        	char *args[] = {"./daniel1", NULL};
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 
			execv(args[0], args);
            exit(0); 
        }
        else
        {
        	sleep(1);
        	wait(NULL);
        }
    } 
}