#include <sys/ipc.h>
#include <stdlib.h>
#include <errno.h>

int main()
{   
    key_t semkey;
    if ((semkey = ftok(".", 5)) == (key_t) -1) 
    {
        perror("IPC error: ftok"); exit(1);
    }    

    printf("%d", semkey);

    return 0;
}