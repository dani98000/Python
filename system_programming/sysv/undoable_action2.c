#include <stdlib.h> /*EXIT_FAILURE*/
#include <errno.h> /*perror*/
#include <stdio.h> /*printf*/
#include <sys/sem.h> /*sembuf*/
#include <unistd.h> /*sleep*/

#define NUM_ITERETAIONS 1000000
#define WITH_UNDO

int main()
{   
    key_t sem_key;
    struct sembuf wait_op;
    int sem_id = 0;

    if ((sem_key = ftok("..", 26)) == (key_t) -1) 
    {
        perror("IPC error: ftok"); exit(1);
    }

    wait_op.sem_num = 0;
    wait_op.sem_op = -1;

    #ifdef WITH_UNDO
    wait_op.sem_flg = SEM_UNDO;
    #endif
    
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

    sleep(1);

    printf("Crashing\n");
    *(int *)(0x0) = 100; 


    return 0;
}
