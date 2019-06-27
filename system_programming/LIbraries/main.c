#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

void Foo();
void Bar1();
void Bar2();
int x = 5;

typedef void (add_func)();

int main()
{
	void *lib_handle = NULL;
	add_func *add;
	
	lib_handle = dlopen("./libso2.so",RTLD_LAZY);
	if(!lib_handle)
	{
		fprintf(stderr, "%s\n",dlerror());
		exit(1);
	}
	
	*(void **)(&add) = dlsym(lib_handle, "Bar2");

	Foo();
	Bar1();
	add();
	printf("%p",&x);
	
	return 0;
}
