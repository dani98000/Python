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
#include <assert.h>/*assert*/
#include <string.h>/*memset*/
#include <errno.h>/*errno*/
#include <string.h>/*memset*/

#include "watchdog.h"
#include "scheduler.h"

#define WD_PATH "./wd"
#define UNUSED(X) (void)(X)
#define FREQUENCY (1)
#define SEM_PERMS (0600)
#define NUM_SEMS (2)
#define BUFF_SIZE (8)
#define NUM_LIVES (3);

union semun
{
    int val;  
    struct semid_ds *buf;  
    unsigned short *array;  
    struct seminfo *__buf;  
};

pthread_t g_thread;
int g_wd_pid = -1;
int g_sem_id = 0;
char **new_argv = NULL;
int g_should_stop = 0;
volatile sig_atomic_t g_got_signal = 0;
volatile sig_atomic_t g_got_usr2 = 0;

static long HeartBeat(void *params);
static long CheckWatchDog(void *params);
static int ReviveWD(char *argv[]);

static void *SchedulerRun(void *scheduler);
static int RunThread(scd_t *scheduler);
static int CreateWatchDogIfNeeded();

static void Sigusr1_handler(int sig, siginfo_t *info, void *context);
static void Sigusr2_handler(int signum);

static int SemDestroy();
static void DestroyArgv(char *argv[]);

static int GetSemVal(int semnum);
static int MakeArgv(char *argv[], int argc, int proj_id);
static int SemInit(int proj_id, char **argv);
static int SignalsInit();
static int Init(int argc, char *argv[], int proj_id);
static scd_t *InitScheduler(char **arg_buffer);

int WDStart(int argc, char *argv[], int proj_id)
{
	key_t sem_key = 0;
    struct sembuf app_ready = {1,1,0};
	scd_t *scheduler = NULL;
	int status = 0;

	assert(argv);
	assert(argc > 0);

	status = Init(argc, argv, proj_id);
	if(status != WD_OK)
	{
		return status;
	}

	scheduler = InitScheduler(new_argv);
	if(NULL == scheduler)
	{
		return WD_E_MEM;
	}

    if (semop(g_sem_id, &app_ready, 1) == -1) 
    {
		return WD_E_SEM;
    }	

	status = CreateWatchDogIfNeeded();
	if(status != WD_OK)
	{
		return status;
	}

    status = RunThread(scheduler);

    return status;
}

static scd_t *InitScheduler(char **arg_buffer)
{
    unid_t task_send_sig;
    unid_t task_check_sig;
    scd_t *scheduler = NULL;

    assert(arg_buffer);

    scheduler = ScdCreate();
    if (!scheduler)
    {
        return NULL;
    }  

    task_send_sig = ScdAdd(scheduler, FREQUENCY, HeartBeat, NULL);
	task_check_sig = ScdAdd(scheduler, FREQUENCY, CheckWatchDog, new_argv);
    
    if (UIDIsBad(task_send_sig) || UIDIsBad(task_check_sig))
    {
        ScdDestroy(scheduler);  
         
        return NULL;
    }
    
    return scheduler;
}

void WDStop()
{
	g_should_stop = 1;
	int times = 5;

	while(times && !g_got_usr2)
	{
		kill(g_wd_pid, SIGUSR2);
		sleep(1);
		--times;

    }
    kill(g_wd_pid, SIGKILL);

    DestroyArgv(new_argv);
    SemDestroy(g_sem_id);

	pthread_join(g_thread, NULL);
}

static int Init(int argc, char *argv[], int proj_id)
{
	int status = 0;

	assert(argc);
	assert(argv);

	status = SignalsInit();
	if(status != WD_OK)
	{
		return status;
	}
	
	status = SemInit(proj_id, argv);
	if(status != WD_OK)
	{
		return status;
	}

	status = MakeArgv(argv, argc, proj_id);
	if(status != WD_OK)
	{
		return status;
	}

	return WD_OK;
}

static int CreateWatchDogIfNeeded()
{
	struct sembuf wd_ready = {0,-1,0};

	if(0 == GetSemVal(0))
    {
    	g_wd_pid = fork();
    	if (g_wd_pid < 0) 
    	{ 
    		return WD_E_EXEC;
    	}
    	if(g_wd_pid == 0)
    	{
    		if(-1 == execv(new_argv[0], new_argv))
    		{
    			return WD_E_EXEC;
    		}
    		exit(0);
    	}

    	if (semop(g_sem_id, &wd_ready, 1) == -1) 
    	{
			return WD_E_SEM;
    	}
    }

    return WD_OK;
}

static long HeartBeat(void *params)
{	
	UNUSED(params);
	
	if(!g_should_stop && g_wd_pid != -1)
	{
		kill(g_wd_pid, SIGUSR1);
	}
	else if(g_should_stop)
	{
		return -1;
	}

	return WD_OK;			
}

static long CheckWatchDog(void *params)
{	
	UNUSED(params);

	static int lives = NUM_LIVES;
	if(g_should_stop)
	{
		return -1;
	}
	else
	{
		if(lives == 0 && !g_got_signal)
		{
			ReviveWD((char **)params);
			lives = NUM_LIVES;
		}
		else if(g_got_signal)
		{
			lives = NUM_LIVES;
			g_got_signal = 0;
		}
		else
		{
			--lives;
		}
	}
	return WD_OK;			
}

static int ReviveWD(char *argv[])
{
	struct sembuf wd_ready = {0,-2,0};

    assert(argv);

	g_wd_pid = fork();
	if (g_wd_pid < 0) 
    { 
    	return WD_E_EXEC;
    }
	else if(g_wd_pid == 0)
	{
		execv(argv[0], argv);
		exit(0);
	}

    if (semop(g_sem_id, &wd_ready, 1) == -1) 
    {
		return WD_E_SEM;
    }

    return WD_OK;
}

static int RunThread(scd_t *scheduler)
{
	assert(scheduler);

    if (0 != pthread_create(&g_thread, NULL, SchedulerRun, scheduler))
    {
		return WD_E_THREAD;
    }

	return WD_OK;
}

static void *SchedulerRun(void *scheduler)
{
	assert(scheduler);

	ScdRun((scd_t *)scheduler);
	ScdDestroy(scheduler);

	return NULL;
}

static int GetSemVal(int semnum)
{
	union semun arg;  

    return semctl(g_sem_id, semnum, GETVAL, arg);
}

static int SemDestroy()
{
	if(-1 == semctl(g_sem_id, 0, IPC_RMID))
	{
		return WD_E_SEM;
	}

	return WD_OK;
}

static int MakeArgv(char *argv[], int argc, int proj_id)
{
	int i = 0;
	char *buffer = NULL;

	assert(argv);

	buffer = (char *)malloc(sizeof(*buffer) * BUFF_SIZE);
	if(NULL == buffer)
	{
		return WD_E_MEM;
	}

	new_argv = (char **)malloc((argc + 3) * sizeof(*new_argv));
	if(NULL == new_argv)
	{
		return WD_E_MEM;
	}

	sprintf(buffer, "%d", proj_id);
	new_argv[0] = WD_PATH;
	new_argv[1] = buffer;
	
	i = 2;
	while(argv[i - 2] != NULL)
	{
		new_argv[i] = argv[i - 2];
		++i;
	}
	new_argv[i] = NULL;

	return WD_OK;
}

static void DestroyArgv(char *argv[])
{
	assert(argv);

	free(argv[1]);
	free(argv);
}

static int SemInit(int proj_id, char **argv)
{
	int sem_key = 0;

	assert(argv);

	if ((sem_key = ftok(argv[0], proj_id)) == (key_t) -1) 
    {
    	return WD_E_SEM;
    }

    g_sem_id = semget(sem_key, SEM_PERMS, IPC_CREAT | IPC_EXCL | SEM_PERMS);
    if (errno == EEXIST)
    {
    	g_sem_id = semget(sem_key, 2, 0600);
    	if(-1 == g_sem_id)
    	{
    		return WD_E_SEM;
    	}
    }

    return WD_OK;
}

static int SignalsInit()
{
	struct sigaction action1;
	struct sigaction action2;

    memset(&action1,0,sizeof(struct sigaction));
    memset(&action2,0,sizeof(struct sigaction));

	action1.sa_flags = SA_SIGINFO;
    action1.sa_sigaction = Sigusr1_handler;
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

static void Sigusr1_handler(int sig, siginfo_t *info, void *context)
{
	if(g_wd_pid == -1)
	{
		g_wd_pid = info->si_pid;
	}
	else
	{
		g_got_signal = 1;
	}
}

static void Sigusr2_handler(int signum)
{
	UNUSED(signum);
	g_got_usr2 = 1;
}