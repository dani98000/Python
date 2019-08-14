#include <stdio.h>

#include "task.h"
#include <time.h>

void test()
{
	unid_t uid = UIDCreate();
	unid_t uid2 = UIDCreate();
	printf("%d, %ld %ld, %lu\n", uid.pid, uid.time.tv_sec, uid.time.tv_usec, uid.counter);
	printf("%d, %ld %ld, %lu\n", uid2.pid, uid2.time.tv_sec, uid2.time.tv_usec, uid2.counter);
	printf("%d, %ld %ld, %lu\n", bad_uid.pid, bad_uid.time.tv_sec, bad_uid.time.tv_usec, 		    	bad_uid.counter);
	printf("is same:%d\n", UIDIsSame(uid, uid));
	printf("is same:%d\n", UIDIsSame(uid, uid2));	
	printf("uid is bad:%d\n", UIDIsBad(bad_uid));
	printf("%d\n", time(NULL));
}

int main()
{
	test();
	
	return 0;
}
