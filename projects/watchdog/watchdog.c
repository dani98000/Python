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
static int ReviveApp(char *argv[]);
static int SemDestroy(int g_sem_id);

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

	SignalsInit();

	g_sem_id = SemInit(argv);
	printf("sem id: %d\n", g_sem_id);
	g_target_pid = getppid();

	ScdAdd(scheduler, 1, HeartBeat, scheduler);
    ScdAdd(scheduler, 1, CheckApp, argv);

	if (semop(g_sem_id, &wd_ready, 1) == -1) 
    {
    	return WD_E_SEM;
    }

    if (semop(g_sem_id, &app_ready, 1) == -1) 
    {
    	return WD_E_SEM;
    }

    ScdRun(scheduler);
}

static long HeartBeat(void *params)
{	
	UNUSED(params);
	
	if(!g_should_stop)
	{
		kill(g_target_pid, SIGUSR1);
	}
	else
	{
		kill(g_target_pid, SIGUSR2);
		ScdDestroy((scd_t *) params);
	}

	return 0;			
}

static int SemDestroy(int g_sem_id) /*TODO : Think if sem id should be global...*/
{
	if(-1 == semctl(g_sem_id, 0, IPC_RMID))
	{
		return WD_E_SEM;
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
			if(!ReviveApp((char **) params))/*If Revived successfully reset lives*/
			{
				lives =  3;
			}
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

static int ReviveApp(char *argv[])
{
	struct sembuf app_ready = {1,-1,0};

	g_target_pid = fork();
	if(g_target_pid == 0)
	{
		execv(argv[2], argv+2);
	}

	if (semop(g_sem_id, &app_ready, 1) == -1) 
    {
    	return WD_E_SEM;
    }

    return 0;
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
	g_should_stop = 1;
}

static int SemInit(char *argv[])
{
	int sem_key = 0;
	int g_sem_id = 0;
	int proj_id = atoi(argv[1]);

	if ((sem_key = ftok(argv[2], proj_id)) == (key_t) -1) 
    {
    	return WD_E_SEM;
    }
     
    g_sem_id = semget(sem_key, 2, 0600);
    if (g_sem_id == -1) 
    {
    	return WD_E_SEM;
    }

    return g_sem_id;
}