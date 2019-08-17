#include <sys/ipc.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/sem.h>/*sembuf*/
#include <sys/msg.h>

#define NUM_ITERATIONS 1

int main()
{   
    key_t sem_key;
    struct sembuf wait_op;
    struct sembuf post_op;
    int sem_id = 0;
    int counter = 0;
    int val = 1;

    if ((sem_key = ftok("..", 59)) == (key_t) -1) 
    {
        perror("IPC error: ftok"); exit(1);
    }


    if (semctl(sem_id, 0, SETVAL, 1) < 0) 
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    wait_op.sem_num = 1;
    wait_op.sem_op = -1;

    sem_id = semget(sem_key, 1, IPC_CREAT | IPC_EXCL | 0600);
    if (sem_id == -1) 
    {
        perror("semget");
        exit(EXIT_FAILURE); 
    }

    while(counter < NUM_ITERATIONS)
    {  
        
        sleep(5);
        printf("ping\n"); 
        
        if (semop(sem_id, &wait_op, 1) == -1) 
        {
            perror("semop(post_op)");
            return 0;
        }

        ++counter;
    }

    printf("Finished!!!\n");

    return 0;
}