#include <stdlib.h>/* EXIT_FAILURE */
#include <stdio.h> /* printf */
#include <sys/sem.h> /*sembuf*/
#include <signal.h> /* sigaction */
#include <unistd.h> /* sleep */
#include <pthread.h>/*threads*/
#include <stddef.h>

#include "watchdog.h"
#include "scheduler.h"

#define UNUSED(X) (void)(X)

int g_target_pid = 0;
int g_sem_id = 0;

volatile sig_atomic_t g_got_signal = 0;
volatile sig_atomic_t g_should_stop = 0;

static long HeartBeat(void *params);
static long CheckApp(void *params);
static void SignalsInit();
static void sigusr1_handler(int signum);
static void sigusr2_handler(int signum);
static int SemInit(char **argv);
static void ReviveApp(char *argv[]);

int main(int argc, char *argv[])
{
	struct sembuf wd_ready = {0,2,0};
    struct sembuf app_ready = {1,-1,0};
	scd_t *scheduler = ScdCreate();

	struct sigaction action1;
	struct sigaction action2;

    action1.sa_handler = sigusr1_handler;
    sigaction(SIGUSR1, &action1, NULL);

    action2.sa_handler = sigusr2_handler;
    sigaction(SIGUSR2, &action2, NULL);

	/*SignalsInit();*/

	g_sem_id = SemInit(argv);
	printf("sem id: %d\n", g_sem_id);
	g_target_pid = getppid();

	ScdAdd(scheduler, 1, HeartBeat, NULL);
    ScdAdd(scheduler, 1, CheckApp, argv);

	if (semop(g_sem_id, &wd_ready, 1) == -1) 
    {
    	perror("semop(wd_ready)");
    	return 0;
    }

    if (semop(g_sem_id, &app_ready, 1) == -1) 
    {
    	perror("semop(app_ready)");
    	return 0;
    }

    ScdRun(scheduler);
}

static long HeartBeat(void *params)
{	
	UNUSED(params);
	
	if(!g_should_stop)
	{
		printf("%d\n", g_target_pid);
		kill(g_target_pid, SIGUSR1);
	}

	return 0;			
}

static long CheckApp(void *params)
{	
	UNUSED(params);

	static int lives = 3;

	if(g_should_stop)
	{
		return -1;
	}
	else
	{
		if(lives == 0 && !g_got_signal)
		{
			ReviveApp((char **) params);
			lives =  3;
		}
		else if(g_got_signal)
		{
			lives = 3;
			g_got_signal = 0;
		}
		else
		{
			--lives;
		}
	}
	return 0;			
}

static void ReviveApp(char *argv[])
{
	struct sembuf app_ready = {1,-1,0};

	g_target_pid = fork();
	if(g_target_pid == 0)
	{
		execv(argv[2], argv+2);
	}

	if (semop(g_sem_id, &app_ready, 1) == -1) 
    {
  		perror("semop(app_ready)");
    	return;
    }
}

static void SignalsInit()
{
    struct sigaction action;

    action.sa_handler = sigusr1_handler;
    sigaction(SIGUSR1, &action, NULL);

    action.sa_handler = sigusr2_handler;
    sigaction(SIGUSR2, &action, NULL);
}

static void sigusr1_handler(int signum)
{
	UNUSED(signum);
	printf("I am the watch |dog| and i got the signal\n");
	g_got_signal = 1;
}

static void sigusr2_handler(int signum)
{
	UNUSED(signum);

	g_got_signal = 1;
}

static int SemInit(char *argv[])
{
	int sem_key = 0;
	int g_sem_id = 0;
	int proj_id = atoi(argv[1]);

	if ((sem_key = ftok(argv[2], proj_id)) == (key_t) -1) 
    {
        perror("IPC error: ftok"); 
        exit(EXIT_FAILURE);
    }
     
    g_sem_id = semget(sem_key, 2, 0600);
    if (g_sem_id == -1) 
    {
        perror("semget(watchdog)");
        exit(EXIT_FAILURE); 
    }

    return g_sem_id;
}