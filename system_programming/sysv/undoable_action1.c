#include <stdlib.h> /*EXIT_FAILURE*/
#include <errno.h> /*perror*/
#include <stdio.h> /*printf*/
#include <sys/sem.h> /*sembuf*/
#include <unistd.h> /*sleep*/

union semun
{
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  
};

void init_semaphore( int sid, int semnum, int initval)
{
    union semun semopts;    
    semopts.val = initval;
    semctl( sid, semnum, SETVAL, semopts);
}

int main()
{   
    key_t sem_key;
    struct sembuf wait_op;
    int sem_id = 0;
    int counter = 0;

    if ((sem_key = ftok("..", 26)) == (key_t) -1) 
    {
        perror("IPC error: ftok"); exit(1);
    }

    wait_op.sem_num = 0;
    wait_op.sem_op = -1;

    sem_id = semget(sem_key, 2, IPC_CREAT | IPC_EXCL | 0600);

    init_semaphore(sem_id, 0, 1);

    if (sem_id == -1) 
    {
        perror("semget");
        exit(EXIT_FAILURE); 
    }

    
    printf("ping\n"); 
    sleep(6);
    if (semop(sem_id, &wait_op, 1) == -1) 
    {
        perror("semop(post_op)");
        return 0;
    }
    
    ++counter;

    printf("Finished!!!\n");

    return 0;
}