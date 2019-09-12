#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct Class metadata;
typedef void (*vfunc_t)(void *);
enum Hierarchy{DERIVED,SUPER};
#define TOSTRING 1

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

typedef struct Animal
{
	Object obj;
	int a;
	int num_legs;
	int num_masters;
	int ID;
} Animal;

typedef struct Dog
{
	Animal animal;

} Dog;

typedef struct Cat
{
	Animal animal;
	
} Cat;

int g_animal_counter = 0;
int g_animal_flag = 0;
int g_dog_flag = 0;

/*****Start of ANIMAL FUNCTIONS******/
void sayHello(void *args)
{
		printf("Animal Hello!\n");
		printf("I have %d legs\n", ((struct Animal *)args)->num_legs);
}

void showCounter()
{
	printf("counter: %d\n", g_animal_counter);
}

char *AnimalToString(void *args)
{
	char *buffer = malloc(sizeof(char) * 80);
	sprintf(buffer, "Animal with ID: %d", ((struct Animal *)args)->ID);
	printf("Animal toString\n");

	return buffer;
}

int getNumMasters(void *args)
{
	Animal *animal = (Animal *)args;

	return animal->num_masters;
}
/*****End of ANIMAL FUNCTIONS******/

/*****Start of Default Functions*****/
char *DefaultToString(void *args)
{
	char *buffer = malloc(sizeof(char) * 80);
	sprintf(buffer, "il.co.ilrd.java2c.Animal@6bc7c054");
	printf("default toString\n");

	return buffer;
}
/*****End of Default Functions*****/

vfunc_t vtable_animal[] = {sayHello ,(void(*)(void *))AnimalToString, (void(*)(void *))getNumMasters};
vfunc_t vtable_object[] = {NULL ,(void(*)(void *))DefaultToString};
vfunc_t vtable_dog[] = {NULL};

metadata object_metadata = {"Object", sizeof(Object), NULL, &vtable_object};
metadata Animal_metadata = {"Animal", sizeof(struct Animal), &object_metadata, &vtable_animal};
metadata Dog_metadata = {"Dog", sizeof(struct Dog), &Animal_metadata, &vtable_dog};

Object *ObjAlloc(metadata *md)
{
	Object *obj = (Object *)malloc(sizeof(*obj));
	void *class = (void *)malloc(md->size); 
	obj->class = md;
	class = (Object *)obj;

	return obj;
}

int InvokeInt(Object *obj, int index, void *args, enum Hierarchy h)
{
	vfunc_t fp = 0;

	if(h == DERIVED)
	{
		fp= (*(obj->class->vtable))[index];
	}
	else
	{
		fp= (*(obj->class->super_class->vtable))[index];
	}

	return ((int (*)(void *))fp)(args);
}

char *InvokeString(Object *obj, int index, void *args, enum Hierarchy h)
{
	vfunc_t fp = 0;

	if(h == DERIVED)
	{
		fp = (*(obj->class->vtable))[index];
	}
	else
	{
		fp= (*(obj->class->super_class->vtable))[index];
	}

	return ((char *(*)(void *))fp)(args);
}

void InvokeMethod(Object *obj, int function_index, void *args)
{
		(*(obj->class->vtable))[function_index](args);
}

void AnimalStaticInitializers()
{
	if(!g_animal_flag)
	{
		printf("Static block Animal 1\n");
		printf("Static block Animal 2\n");
	}

	g_animal_flag = 1;
}

void AnimalInstanceInitializers()
{
	printf("Instance initialization block Animal\n");
}

void AnimalCtor1(struct Animal *animal)
{
	printf("Animal Ctor\n");
	animal->ID = ++g_animal_counter;
	InvokeMethod((Object *)animal, 0, (Object *)animal);/*sayhello()*/
	showCounter();
	printf("%s\n",InvokeString((Object *)animal, 1, animal, DERIVED));/*toString();*/
	printf("%s\n",InvokeString((Object *)animal, 1, animal, SUPER));
}

void AnimalCtor2(struct Animal *animal, int num_masters)
{
		printf("Animal Ctor int");
		animal->ID = ++g_animal_counter;
		animal->num_masters = num_masters;
}

void DogStaticInitializers()
{
	if(!g_dog_flag)
	{
		printf("Static block Dog");
	}

	g_dog_flag = 1;
}

int main()
{
	Animal *animal = (Animal *)ObjAlloc(&Animal_metadata);
	Object *obj = (Object *)animal;
	int res = 0;
	animal->num_legs = 5;
	animal->num_masters = 1;

	AnimalStaticInitializers();
	AnimalInstanceInitializers();
	AnimalCtor1(animal);

	/*res = InvokeInt(obj, 2, animal, DERIVED);
	printf("num_masters: %d\n", res);*/

	return 0;
}