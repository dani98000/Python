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

    if ((sem_key = ftok("pong.c", 3)) == (key_t) -1) 
    {
        perror("IPC error: ftok"); exit(1);
    }

    wait_op.sem_num = 0;
    wait_op.sem_op = -1;

    post_op.sem_num = 1;
    post_op.sem_op = 1;

    sem_id = semget(sem_key, 2, IPC_CREAT | IPC_EXCL | 0600);
    if (sem_id == -1) 
    {
        perror("semget");
        exit(EXIT_FAILURE); 
    }
    
    while(counter < NUM_ITERETAIONS)
    {
        if (semop(sem_id, &wait_op, 1) == -1) 
        {
            perror("semop(wait_op)");
            
            return 0;
        }

/*        sleep(1);
*/        printf("pong\n"); 

        if (semop(sem_id, &post_op, 1) == -1) 
        {
            perror("semop(post_op)");
            
            return 0;    
        }
        
        ++counter;
    }

    if (semctl(sem_id, 0, IPC_RMID) < 0) 
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}