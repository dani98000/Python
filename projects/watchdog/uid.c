/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 13/06/2019		*
*	 Reviewer: Roi           	*
*								*
*********************************/
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "uid.h"

const unid_t bad_uid;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 

unid_t UIDCreate()
{
	unid_t uid;
	static size_t counter = 0;
	uid.pid = getpid();
	if(-1 == gettimeofday(&uid.time, NULL))
	{
		return bad_uid;
	}
	
	pthread_mutex_lock(&lock);
	uid.counter = ++counter;
	pthread_mutex_unlock(&lock);

	return uid;
}

int UIDIsSame(unid_t uid1, unid_t uid2)
{
	return(uid1.pid == uid2.pid && uid1.time.tv_sec == uid2.time.tv_sec && uid1.time.tv_usec 						== 	uid2.time.tv_usec && uid1.counter == uid2.counter);
}

int UIDIsBad(unid_t uid)
{
	return(UIDIsSame(uid, bad_uid));
}

