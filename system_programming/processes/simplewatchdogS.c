#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
int main() 
{
    pid_t child_pid = 0;

	int i = 0;

	for(i = 0; i < 10; ++i) 
    { 
        child_pid = system("./daniel1");
        sleep(1);
    } 

}