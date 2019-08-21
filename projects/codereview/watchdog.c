/*******************************************************************************
*	Watchdog Code
	Programmer: Eldad Carin
*   19.08.2019                                                                 *
*******************************************************************************/
#include <stdlib.h>    /* malloc */
#include <string.h>    /* string */
#include <unistd.h>    /* fork */
#include <assert.h>    /* assert    */
#include <signal.h>    /* sigaction */
#include <sys/types.h> /* semop */
#include <sys/ipc.h>   /* semop */
#include <sys/sem.h>   /* semop */

#include "scheduler.h" /* scheduler library header */
#include "watchdog.h"  /* header */
#include "defs.h"      /* colors */

#define SEM_ID_INDEX (1)
#define PATH_INDEX (2)
#define TASK_FREQ (2)
#define NUM_TRIES (3)

enum sem_nums
{
	APP_READY = 0,
	WD_READY = 1,
	NUM_SEMS
};

/* Global Variables ***********************************************************/
static pid_t g_app_pid;
volatile sig_atomic_t g_app_alive = NUM_TRIES;
struct sembuf g_buff_app_post = {APP_READY, 1, 0};
struct sembuf g_buff_wd_wait = {WD_READY, -1, 0};
volatile sig_atomic_t g_should_stop;

/* Functions declarations *****************************************************/
static void GuardApplication(char **argv);
static scd_t *SchedulerInit(char **argv);
static long IsAppAlive(void *params);
static long IAmAlive(void *params); 
static void SigHandlerWD(int signum);
static void SigHandler2(int signum);
static pid_t ExecTheApp(int sem_id, char **argv);
static int SemPost(int sem_id, struct sembuf sembuf);
static int SemWait(int sem_id, struct sembuf sembuf);
static void InitSigactions();


/******************************************************************************/
int main(int argc, char **argv)
{
	GuardApplication(argv);

	return 0;
}

/* WATCHDOG PROCESS ***********************************************************/
static void GuardApplication(char **argv)
{
	int sem_id = 0;
	scd_t *scheduler = NULL;
	unid_t is_app_alive_task;
	unid_t i_am_alive_task;
	
	assert(argv);

	g_app_pid = getppid();

	InitSigactions();

	sem_id = atoi(argv[SEM_ID_INDEX]);
	
	SemPost(sem_id, g_buff_app_post);

	scheduler = SchedulerInit(argv);

	if (NULL != scheduler)
	{
		ScdDestroy(scheduler);
	} 
}


/* SIGUSR & SIGACTION *********************************************************/
static void InitSigactions()
{
	struct sigaction watchdog_sigact; /* SIGUSR1 */
	struct sigaction stop_sigact;     /* SIGUSR2 */

	memset(&watchdog_sigact, 0, sizeof(watchdog_sigact));
	watchdog_sigact.sa_handler = SigHandlerWD; 
	
	memset(&stop_sigact, 0, sizeof(stop_sigact));
	stop_sigact.sa_handler = SigHandler2; 
	
	sigaction(SIGUSR1, &watchdog_sigact, NULL); 
	sigaction(SIGUSR2, &stop_sigact, NULL); 
}

static void SigHandlerWD(int signum)
{
	g_app_alive = 3;
	UNUSED(signum);
}

static void SigHandler2(int signum)
{	
	g_should_stop = 1;
	kill(g_app_pid, SIGUSR2);
	UNUSED(signum);
}

/* SCHEDULER ******************************************************************/
static scd_t *SchedulerInit(char **argv)
{
	unid_t is_app_alive_task;
    unid_t i_am_alive_task;

	scd_t *scheduler = ScdCreate();
	if (NULL == scheduler)
	{
		return NULL;
	}

	is_app_alive_task = ScdAdd(scheduler, TASK_FREQ, IsAppAlive, argv); /* init check task */
	if (UIDIsBad(is_app_alive_task))
	{
		ScdDestroy(scheduler);
		scheduler = NULL;

		return NULL;
	}

	i_am_alive_task = ScdAdd(scheduler, TASK_FREQ, IAmAlive, NULL); /* init signal task */ 
	if (UIDIsBad(is_app_alive_task))
	{
		ScdDestroy(scheduler);
		scheduler = NULL;

		return NULL;
	}

	ScdRun(scheduler);

	return scheduler;
}

/* scheduler task 1of2 - check app is alive */
static long IsAppAlive(void *params) 
{
	char **argv = NULL;
	int sem_id = 0;

	assert(params);

	if (g_should_stop)
	{
		return -1;
	}

	argv = (char **)params;
	sem_id = atoi(argv[SEM_ID_INDEX]);

	--g_app_alive; /* decrement app_is_alive indicator flag */

	if (!g_app_alive) 
	{
		SemPost(sem_id, g_buff_app_post);
		g_app_pid = ExecTheApp(sem_id, argv);
		SemWait(sem_id, g_buff_wd_wait); 
	}

	return 0; /* == non recurring task */
}

/* shceduler task 2of2 - confirm via sigusr1 that watchdog is alive */
static long IAmAlive(void *params) 
{
	if (g_should_stop)
	{
		return -1;
	}

	kill(g_app_pid, SIGUSR1);

	UNUSED(params);
	return 0; /* == non recurring task */
}
/* SEMAPHORE & PROCESS ********************************************************/
static pid_t ExecTheApp(int sem_id, char **argv)
{
    pid_t app_pid = fork();
    
    if (0 == app_pid)  /* if i am child /*/
    {
		sem_id = atoi(argv[SEM_ID_INDEX]);
        execv(argv[PATH_INDEX], &argv[PATH_INDEX]); 
	}

    return app_pid;
}

static int SemPost(int sem_id, struct sembuf sembuf)
{
    if (-1 == semop(sem_id, &sembuf, 1)) 
    {
        return -1;    
    }
}

static int SemWait(int sem_id, struct sembuf sembuf)
{
    return SemPost(sem_id, sembuf);
}