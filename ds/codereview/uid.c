/*******************************************************************************
* Programmer: Eldad Carin
* Reviewer: 
* File: uid code
* Date: 13-06-2019 14:29:25
*******************************************************************************/
/*
struct unid
{
	pid_t pid;
	struct timeval time;
	size_t counter;
}; 
typedef struct unid unid_t;

*/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <unistd.h> /* pid_t */ 
#include <time.h> /* time funcs */

#include "../include/Scheduler/uid.h" /* UID header */

const unid_t bad_uid;
static size_t counter;

unid_t UIDCreate()
{    
    unid_t new_uid;
    
    if (-1 == gettimeofday(&new_uid.time, NULL))
    {
        return bad_uid;
    }
    
    new_uid.pid = getpid();
    new_uid.counter = counter;
    
    ++counter;   
    
    return new_uid;
}

int UIDIsSame(unid_t uid1, unid_t uid2)
{
    
    return (uid1.pid == uid2.pid 
              && uid1.time.tv_sec == uid2.time.tv_sec  
              && uid1.time.tv_usec == uid2.time.tv_usec 
              && uid1.counter == uid2.counter 
                                              ? 1 : 0);                  
}

int UIDIsBad(unid_t uid)
{
    return UIDIsSame(uid, bad_uid);
}
