/*******************************************************************************
*	WatchDogAppside                                                            *
*   Programmer: Eldad Carin                                                    *
*   19.08.2019                                                                 *
*******************************************************************************/
#include <stdio.h>    /* sprintf */
#include <string.h>    /* memcpy */
#include <pthread.h>   /* thread library */
#include <stdlib.h>    /* malloc, srand */
#include <assert.h>    /* assert */
#include <sys/stat.h>  /* fstat */
#include <signal.h>    /* sigaction */
#include <unistd.h>    /* fork */
#include <assert.h>    /* assert */
#include <signal.h>    /* sigaction */
#include <sys/types.h> /* semop */
#include <sys/ipc.h>   /* semop */
#include <sys/sem.h>   /* semop */
#include <errno.h>     /* errno */

#include "scheduler.h" /* g_scheduler library header */
#include "watchdog.h"  /* header */
#include "defs.h"      /* colors */

#define SEM_ID_INDEX (1)
#define PATH_INDEX (0)
#define TASK_FREQ (2)
#define NUM_TRIES (3)
#define NUM_ADD_ARGS (2)
#define ARGV1_MALLOC_SIZE (50)
#define PATH ("./watchdog.out")

enum sem_nums
{
    APP_READY = 0,
    WD_READY = 1,
    NUM_SEMS
};

/* GLOBAL VARIABLES ***********************************************************/
volatile sig_atomic_t g_watchdog_alive = NUM_TRIES;
static pid_t g_wd_pid;
int g_sem_id;
char **g_modified_argv;
pthread_t g_thread;
scd_t *g_scheduler;
struct sembuf g_buff_wd_post = {WD_READY, 1, 0};
struct sembuf g_buff_app_wait = {APP_READY, -1, 0};
volatile sig_atomic_t g_usr2_received;
int g_should_stop;

/* Functions declarations *****************************************************/
static int InitWatchDog(int argc, char **argv, int wd_id);
static void InitUSRSignals();
static int InitSemaphores(char *argv_zero, int wd_id);
static int SetNewSemaphores();
static int CreateModifiedArgV(int argc, char **argv);
static int ActivateInitialWatchDog();
static void *ThreadFunc(void *args);
static int Threading();
static int SchedulerInit();
static long IsWDAlive(void *params);
static long IAmAlive(void *params); 
static void SigHandler1(int signum);
static void SigHandler2(int signum);
static pid_t ExecTheWD();
static int SemPost(struct sembuf sembuf);
static int SemWait(struct sembuf sembuf);
static void DestroyAppSide();

/* CODE ***********************************************************************/
void WDStop()
{
	int times = NUM_TRIES;
	g_should_stop = 1;

    while (!g_usr2_received && times) /* plan A - gracefully */
	{
		kill(g_wd_pid, SIGUSR2);
		--times;
		sleep(1);
	}

	if (!g_usr2_received)
	{
		kill(g_wd_pid, SIGKILL); /* plan B - brute force */
	}

	DestroyAppSide();	
}

static void DestroyAppSide()
{
	semctl(g_sem_id, 0, IPC_RMID);   /* free semaphore */
	
	free(g_modified_argv[SEM_ID_INDEX]);    
	g_modified_argv[SEM_ID_INDEX] = NULL;
	
	free(g_modified_argv);
	g_modified_argv = NULL;
}

int WDStart(int argc, char **argv, int wd_id)
{
    enum status status = WD_OK;

    assert(argv);
    assert(wd_id);

    status = InitWatchDog(argc, argv, wd_id);

    return status;
}

static int InitWatchDog(int argc, char **argv, int wd_id)
{
    enum status status = 0;
        
    assert(argv);
    assert(wd_id);

	InitUSRSignals();

    if (-1 == InitSemaphores(argv[0], wd_id))
    {
    	return WD_E_SEM;
    }
	
    if (-1 == CreateModifiedArgV(argc, argv))
    {
	   	return WD_E_MEM;
    }

	status == SchedulerInit();
    if (WD_OK != status)
    {
        return status;
    }

	if (-1 == ActivateInitialWatchDog())
    {
        return WD_E_MEM;
    }    

	if (WD_OK != Threading())
    {
        return WD_E_THREAD;
    }

    return WD_OK;        
}
/* SIGNAL *********************************************************************/
static void InitUSRSignals()
{
    struct sigaction app_sigact;  /* SIGUSR1 */
    struct sigaction stop_sigact; /* SIGUSR2 */

    memset(&app_sigact, 0, sizeof(app_sigact)); 
    app_sigact.sa_handler = SigHandler1; 

	memset(&stop_sigact, 0, sizeof(stop_sigact)); 
    stop_sigact.sa_handler = SigHandler2; 
    
    sigaction(SIGUSR1, &app_sigact, NULL);     
    sigaction(SIGUSR2, &stop_sigact, NULL);    
}

static void SigHandler1(int signum)
{
	g_watchdog_alive = 3;
	UNUSED(signum);
}

static void SigHandler2(int signum)
{
	g_usr2_received = 1;
	UNUSED(signum);
} 	
/* SEMAPHORE ******************************************************************/
static int InitSemaphores(char *argv_zero, int wd_id)
{
    key_t key;

    assert(argv_zero);

    key = ftok(argv_zero, wd_id);
    if (-1 == key)
    {
        return -1;
    }

    g_sem_id = semget(key, NUM_SEMS, IPC_CREAT | IPC_EXCL | 0666);
    if (0 < g_sem_id) /* case: appside is parent, wd will be child */
    {
    	if (-1 == SetNewSemaphores())
        {
            return -1;
        }        
    }
    else if (EEXIST == errno) /* case: appside is child, wd is parent */
    {
        g_sem_id = semget(key, NUM_SEMS, IPC_CREAT | 0666);
        
        if (-1 == g_sem_id) 
        {
            return -1;
        }
    }
    else /* non-EEXIST semget error, terminate */
    {
        return -1;
    }

    return 0;
}

static int SetNewSemaphores()
{
    if (-1 == semctl(g_sem_id, APP_READY, SETVAL, 0))
    {
        return -1;
    }

    if (-1 == semctl(g_sem_id, WD_READY, SETVAL, 0))
    {
        return -1;
    }
}

static int SemPost(struct sembuf sembuf)
{
    if (-1 == semop(g_sem_id, &sembuf, 1)) /* increment app_ready_sem*/
    {
        return -1;    
    }
}

static int SemWait(struct sembuf sembuf)
{
    return SemPost(sembuf);
}

/* WATCHDOG ACTIVATION ********************************************************/
static int CreateModifiedArgV(int argc, char **argv)
{
    int i = 0;

    assert(argv);

	g_modified_argv = malloc(sizeof(*g_modified_argv) * (argc + NUM_ADD_ARGS + 1));
    if (NULL == g_modified_argv)
    {
        return -1;
    }

    g_modified_argv[PATH_INDEX] = "./watchdog.out";

    g_modified_argv[SEM_ID_INDEX] = malloc(sizeof(char) * ARGV1_MALLOC_SIZE);
    if (NULL == g_modified_argv[SEM_ID_INDEX])
    {
        return -1; 
    }

    sprintf(g_modified_argv[SEM_ID_INDEX], "%d", g_sem_id); /* itoa */

    for (i = 0; i < argc; ++i)
    {
        g_modified_argv[i + NUM_ADD_ARGS] = argv[i];
    }
    
    g_modified_argv[i + NUM_ADD_ARGS] = NULL;
    
    return 0;
}

static int ActivateInitialWatchDog()
{
    int semval = 0;
    
    if (0 == semctl(g_sem_id, APP_READY, GETVAL, 0))
    {
        g_wd_pid = ExecTheWD();

        if (-1 == SemWait(g_buff_app_wait))
        {
            return -1;
        }
    }
    else
    {
        g_wd_pid = getppid();

        if (-1 == SemPost(g_buff_wd_post))
        {
            return WD_E_SEM;
        }        
    }

    return WD_OK; 
}

static pid_t ExecTheWD()
{
    pid_t wd_pid = fork();
    if (0 == wd_pid)  /* if i am child /*/
    {
        if (-1 == execv(g_modified_argv[PATH_INDEX], 
        								&g_modified_argv[PATH_INDEX]))    
        {
            return -1;
        }
    }

    return wd_pid;
}
/* THREAD *********************************************************************/
static void *ThreadFunc(void *args)
{
    ScdRun((scd_t *)args);

    ScdDestroy((scd_t *)args);

    return NULL;
}

static int Threading()
{
    if(0 != pthread_create(&g_thread, NULL, ThreadFunc, g_scheduler))
    {
        return WD_E_THREAD;
    }
    
    if(0 != pthread_detach(g_thread))
    {
		return WD_E_THREAD;
    }
    
	return WD_OK;
}

/* SCHEDULER ******************************************************************/
static int SchedulerInit()
{
	unid_t is_wd_alive_task;
    unid_t i_am_alive_task;
    
    g_scheduler = ScdCreate();
	if (NULL == g_scheduler)
	{	
        return WD_E_MEM;
	}

	is_wd_alive_task = ScdAdd(g_scheduler, TASK_FREQ, IsWDAlive, NULL); /* add check task */
	if (UIDIsBad(is_wd_alive_task))
	{
		ScdDestroy(g_scheduler);
        g_scheduler = NULL;
		
        return WD_E_MEM;
	}

	i_am_alive_task = ScdAdd(g_scheduler, TASK_FREQ, IAmAlive, NULL); /* add signal task */ 
	if (UIDIsBad(i_am_alive_task))
	{
		ScdDestroy(g_scheduler);
        g_scheduler = NULL;

		return WD_E_MEM;
	}

	return WD_OK;
}

/* g_scheduler task 1of2 - check wd is alive */
static long IsWDAlive(void *params) 
{
	if (g_should_stop)
	{
		return -1;
	}

    --g_watchdog_alive; /* decrement wd_is_alive indicator counter */

	if (!g_watchdog_alive) 
	{   
        g_wd_pid = ExecTheWD();

        if (-1 == SemWait(g_buff_app_wait))
        {
            return -1;
        }

        g_watchdog_alive = 3;
    }

	UNUSED(params);
    return 0;
}

/* shceduler task 2of2 - confirm via sigusr1 that watchdog is alive */
static long IAmAlive(void *params) 
{
    if (g_should_stop)
	{
		return -1;
	}

    kill(g_wd_pid, SIGUSR1);
	
	UNUSED(params);
	return 0;
}