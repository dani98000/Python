#include <sys/ipc.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/sem.h>/*semopbuf*/
#include <sys/msg.h>

#define NUM_ITERETAIONS 1000000

int main()
{   
    key_t sem_key;
    struct sembuf wait_op;
    struct sembuf post_op;
    int sem_id = 0;
    int counter = 0;

    if ((sem_key = ftok("..", 59)) == (key_t) -1) 
    {
        perror("IPC error: ftok"); exit(1);
    }

    wait_op.sem_num = 1;
    wait_op.sem_op = -1;
    wait_op.sem_flg = SEM_UNDO;

    sem_id = semget(sem_key, 1, 0600);
    if (sem_id == -1) 
    {
        perror("semget");
        exit(EXIT_FAILURE); 
    }    
        


    if (semop(sem_id, &wait_op, 1) == -1) 
    {
        perror("semop(wait_op)");
        
        return 0;
    }

    printf("locked shared resource\n");

    sleep(1);

    printf("crashing...\n");
    *(int *)(0x0) = 3; /* rip */


    return 0;
}
