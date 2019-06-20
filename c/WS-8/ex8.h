struct functions
{
    void *data;
	void (*Add)(int Input, void *data);
	void (*Print)(void *data);
	void (*Free_memory)(void *data);
};

void AddInt(int Input, void *data);
void AddFloat(int Input, void *data);
void AddString(int Input, void *data);

void PrintInt(void *data);
void PrintFloat(void *data);
void PrintString(void *data);

void FreeMemory(void *data);
void DoNothing(void *data);


