#include <stdlib.h>/* EXIT_FAILURE */
#include <stdio.h> /* printf */
#include <sys/sem.h> /*sembuf*/
#include <signal.h> /* sigaction */
#include <unistd.h> /* sleep */
#include <pthread.h>/*threads*/
#include <errno.h>/*errno*/
#include <string.h>/*memset*/
#include <assert.h>/*assert*/

#include "watchdog.h"
#include "scheduler.h"

#define UNUSED(X) (void)(X)
#define FREQUENCY 1

int g_target_pid = 0;
int g_sem_id = 0;

volatile sig_atomic_t g_got_signal = 0;
volatile sig_atomic_t g_should_stop = 0;

static long HeartBeat(void *params);
static long CheckApp(void *params);
static void SignalsInit();
static void Sigusr1_handler(int signum);
static void Sigusr2_handler(int signum);
static int SemInit(char **argv);
static int ReviveApp(char *argv[]);
static int SemDestroy(int g_sem_id);

int main(int argc, char *argv[])
{
	struct sembuf wd_ready = {0,2,0};
    struct sembuf app_ready = {1,-1,0};
	scd_t *scheduler = ScdCreate();

	assert(argv);

	SignalsInit();

	g_sem_id = SemInit(argv);
	g_target_pid = getppid();

	ScdAdd(scheduler, FREQUENCY, HeartBeat, NULL);
    ScdAdd(scheduler, FREQUENCY, CheckApp, argv);

	if (semop(g_sem_id, &wd_ready, 1) == -1) 
    {
    	return WD_E_SEM;
    }

    ScdRun(scheduler);
    ScdDestroy(scheduler);
    SemDestroy(g_sem_id);

    return 0;
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

		return -1;
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

    struct sembuf app_ready = {1,-1,0};

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
		exit(1);
	}

	if (semop(g_sem_id, &app_ready, 1) == -1) 
    {
    	return WD_E_SEM;
    }

    return 0;
}

static void SignalsInit()
{
	struct sigaction action1;
	struct sigaction action2;

    memset(&action1,0,sizeof(struct sigaction));
    memset(&action2,0,sizeof(struct sigaction));

    action1.sa_handler = Sigusr1_handler;
    sigaction(SIGUSR1, &action1, NULL);

    action2.sa_handler = Sigusr2_handler;
    sigaction(SIGUSR2, &action2, NULL);
}

static void Sigusr1_handler(int signum)
{
	UNUSED(signum);
	printf("I am the watch |dog| and i got the signal\n");
	g_got_signal = 1;
}

static void Sigusr2_handler(int signum)
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
    	printf("daniel1\n");
    	return WD_E_SEM;
    }
     
    g_sem_id = semget(sem_key, 2, 0600);
    if (g_sem_id == -1) 
    {
    	printf("daniel2\n");
    	return WD_E_SEM;
    }

    return g_sem_id;
}