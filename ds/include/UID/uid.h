/*struct uid 
{
	pid_t pid;
	struct timeval time;
	size_t counter;
}*/

typedef struct uid uid_t

uid_t *UIDCreate();
UIDIsSame(uid_t uid1, uid_t uid2);
int UIDIsBad(uid_t uid);
