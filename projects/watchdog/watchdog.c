/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 21/08/2019		*
*	 Reviewer: Yoav        		*
*								*
*********************************/
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
#define FREQUENCY (1)
#define SEM_PERMS (0600)
#define NUM_SEMS (2)

int g_target_pid = 0;
int g_sem_id = 0;

volatile sig_atomic_t g_got_signal = 0;
volatile sig_atomic_t g_should_stop = 0;

static long HeartBeat(void *params);
static long CheckApp(void *params);

static void Sigusr1_handler(int signum);
static void Sigusr2_handler(int signum);

static int SignalsInit();
static int SemInit(char **argv);

static int ReviveApp(char *argv[]);
static int SemDestroy(int g_sem_id);

int main(int argc, char *argv[])
{
	struct sembuf wd_ready = {0,2,0};
	int status = 0;
	scd_t *scheduler = ScdCreate();

	assert(argv);

	status = SignalsInit();
	if(status != WD_OK)
	{
		return status;
	}

	status = SemInit(argv);
	if(status != WD_OK)
	{
		return status;
	}

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

    return WD_OK;
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

	return WD_OK;			
}

static int SemDestroy(int g_sem_id)
{
	if(-1 == semctl(g_sem_id, 0, IPC_RMID))
	{
		return WD_E_SEM;
	}

	return WD_OK;
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

	return WD_OK;			
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

    return WD_OK;
}

static int SignalsInit()
{
	struct sigaction action1;
	struct sigaction action2;

    memset(&action1,0,sizeof(struct sigaction));
    memset(&action2,0,sizeof(struct sigaction));

    action1.sa_handler = Sigusr1_handler;
    if(-1 == sigaction(SIGUSR1, &action1, NULL))
    {
    	return WD_E_SIGACT;
    }

    action2.sa_handler = Sigusr2_handler;
    if(-1 == sigaction(SIGUSR2, &action2, NULL))
    {
       	return WD_E_SIGACT;
    }

    return WD_OK;
}

static void Sigusr1_handler(int signum)
{
	UNUSED(signum);
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
	int proj_id = atoi(argv[1]);

	if ((sem_key = ftok(argv[2], proj_id)) == (key_t) -1) 
    {
    	return WD_E_SEM;
    }
     
    g_sem_id = semget(sem_key, NUM_SEMS, SEM_PERMS);
    if (g_sem_id == -1) 
    {
    	return WD_E_SEM;
    }

    return WD_OK;
}