#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Class metadata;
typedef void (*vfunc_t)(void *);

void test_func(void *args)
{
	(void)(args);
	printf("Test Func\n");
}

vfunc_t vtable[] = {NULL ,test_func};

struct Class
{
	char *name;
	size_t size;
	metadata *super_class;
	vfunc_t (*vtable)[];
};

typedef struct Object
{
	metadata *class;
} Object;

struct Animal
{
	Object obj;
	int a;
};

metadata Animal_metadata = 
{
	"Animal",
	sizeof(struct Animal),
	NULL,
	&vtable
};

metadata object_metadata = 
{
	"Object",
	sizeof(Object),
	NULL,
	NULL
};

/*void InitFuncTable()
{
	vtable = {&test_func};
}*/

Object *Alloc(metadata md)
{
	Object *Animal_obj= (Object *)malloc(sizeof(*Animal_obj));
	Animal_obj->class = (metadata *)&Animal_metadata;

	return Animal_obj;
}

int main()
{
	Object *new = Alloc(Animal_metadata);
	(*(new->class->vtable))[1](NULL);

	return 0;
}