/******************************************
*                _____  __     _   ___    *
*               (  _  )(  )   / ) / _ \   *
*    |\---/|     )(_)(  )(__ / _ \\_  /   *
*    | ,_, |    (_____)(____)\___/ (_/    *
*     \_`_/-..----.                       *
*  ___/ `   ' ,""+ \                      *
* (__...'   __\    |`.___.';              *
*  (_,...'(_,.`__)/'.....+                *
*            *********************        *
*            -Exersice: Java2C 			  *
*			 -Name: Daniel Maizel         *
*			 -Reviewer: Roi 	          *
******************************************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

enum FUNC{SAY_HELLO, TO_STRING, GET_NUM_MASTERS, FINALIZE};

#define NUM_ANIMALS 5
#define BUFF_SIZE 100

typedef struct Class metadata;
typedef void (*vfunc_t)(void *);
typedef struct Object Object;

int g_animal_counter = 0;
int g_animal_flag = 0;
int g_dog_flag = 0;
int g_cat_flag = 0;
int g_legenderyanimal_flag = 0;

struct Class
{
	char *name;
	size_t size;
	metadata *super_class;
	vfunc_t (*vtable)[];
};

void InvokeMethod(Object *obj, int index, void *args);
vfunc_t GetVirtualMethod(Object *obj, int index);
vfunc_t GetSuperMethod(metadata *curr_meta, int index);

/***** Start of Class Object ******/
void *ObjAlloc(metadata *md);

struct Object
{
	metadata *class;
};

char *DefaultToString(void *args)
{
	char *buffer = malloc(sizeof(char) * 80);
	if(buffer == NULL)
	{
		return NULL;
	}
	sprintf(buffer, "il.co.ilrd.java2c.%s@6bc7c054", ((Object *)args)->class->name);

	return buffer;
}

void ObjectFinalize(void *args)
{
	(void)args;
	printf("Default Finalize");
}

vfunc_t vtable_object[] =   {NULL, 
							(void(*)(void *))DefaultToString, 
							NULL, 
							ObjectFinalize};

metadata object_metadata = {"Object", 
							sizeof(Object), 
							NULL, 
							&vtable_object};

/******* End of Class Object ******/

/***** Start of Class Animal ******/
typedef struct Animal
{
	Object obj;
	int a;
	int num_legs;
	int num_masters;
	int ID;
} Animal;

void AnimalSayHello(void *args)
{
		printf("Animal Hello!\n");
		printf("I have %d legs\n", ((Animal *)args)->num_legs);
}

void showCounter()
{
	printf("counter: %d\n", g_animal_counter);
}

char *AnimalToString(void *args)
{
	char *buffer = malloc(sizeof(char) * 80);
	if(buffer == NULL)
	{
		return NULL;
	}

	sprintf(buffer, "Animal with ID: %d", ((Animal *)args)->ID);

	return buffer;
}

int getNumMasters(void *args)
{
	Animal *animal = (Animal *)args;

	return animal->num_masters;
}

void AnimalFinalize(void *args)
{
	vfunc_t fp = NULL;
	(void)args;
	printf("finalize Animal with ID:%d", ((Animal *)args)->ID);
	fp = GetVirtualMethod((Object *)args, FINALIZE);
	fp((Animal *)args);
}

vfunc_t vtable_animal[] =   {AnimalSayHello, 
							(void(*)(void *))AnimalToString, 
							(void(*)(void *))getNumMasters, 
							AnimalFinalize};

metadata Animal_metadata = {"Animal", 
							sizeof(Animal), 
							&object_metadata, 
							&vtable_animal};

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

void AnimalCtor1(Animal *animal)
{
	vfunc_t fp = NULL;
	printf("Animal Ctor\n");
	animal->ID = ++g_animal_counter;
	fp = GetVirtualMethod((Object *)animal, SAY_HELLO);
	fp((Object *)animal);
	showCounter();
	fp = GetVirtualMethod((Object *)animal, TO_STRING);
	printf("%s\n",((char *(*)(void *))fp)(animal) );
	fp = GetSuperMethod(&Animal_metadata ,TO_STRING);
	printf("%s\n",((char *(*)(void *))fp)(animal));
}

void AnimalCtor2(Animal *animal, int num_masters)
{
		printf("Animal Ctor int\n");
		animal->ID = ++g_animal_counter;
		animal->num_masters = num_masters;
}

Animal *CreateAnimal()
{
	Animal *animal = (Animal *)ObjAlloc(&Animal_metadata);
	animal->num_masters = 1;
	animal->num_legs = 5;

	AnimalStaticInitializers();
	AnimalInstanceInitializers();
	AnimalCtor1(animal);

	return animal;
}

/******* End of Class Animal ******/

/***** Start of Class Dog ******/
typedef struct Dog
{
	Animal animal;
	int num_legs;
} Dog;

void DogSayHello(void *args)
{
		printf("Dog Hello!\n");
		printf("I have %d legs\n", ((Dog *)args)->num_legs);
}

char *DogToString(void *args)
{
	char *buffer = malloc(sizeof(char) * 80);
	if(buffer == NULL)
	{
		return NULL;
	}

	sprintf(buffer, "Dog with ID: %d", ((Animal *)args)->ID);

	return buffer;
}

void DogFinalize(void *args)
{
	(void)args;
	printf("finalize Dog with ID:%d", ((Animal *)args)->ID);
	InvokeMethod((Object *)args, FINALIZE, (Dog *)args);
}

vfunc_t vtable_dog[] = {DogSayHello ,
						(void(*)(void *))DogToString, 
						(void(*)(void *))getNumMasters, 
						DogFinalize};

metadata Dog_metadata = {"Dog", 
						sizeof(Dog), 
						&Animal_metadata, 
						&vtable_dog};

void DogStaticInitializers()
{
	if(!g_dog_flag)
	{
		printf("Static block Dog\n");
	}

	g_dog_flag = 1;
}

void DogInstanceInitializers()
{
	printf("Instance initialization block Dog\n");
}

void DogCtor(Dog *dog)
{
	AnimalCtor2(&(dog->animal), 2);
	DogInstanceInitializers();
	printf("Dog Ctor\n");
}

Dog *CreateDog()
{
	Dog *dog = ObjAlloc(&Dog_metadata);
	dog->animal.num_legs = 5;
	dog->animal.num_masters = 1;
	dog->num_legs = 4;
	DogStaticInitializers();
	AnimalInstanceInitializers();
	DogCtor(dog);

	return dog;
}

/******* End of Class Dog ******/


/***** Start of Class Cat ******/
typedef struct Cat
{
	Animal animal;
	int num_masters;
	char *colors;
} Cat;

char *CatToString(void *args)
{
	char *buffer = malloc(sizeof(char) * 80);
	if(buffer == NULL)
	{
		return NULL;
	}
	
	sprintf(buffer, "Cat with ID: %d", ((Animal *)args)->ID);

	return buffer;
}

void CatFinalize(void *args)
{
	(void)args;
	printf("finalize Cat with ID:%d", ((Animal *)args)->ID);
	InvokeMethod((Object *)args, FINALIZE, (Cat *)args);
}

vfunc_t vtable_cat[] = {AnimalSayHello,
						(void(*)(void *))CatToString, 
						(void(*)(void *))getNumMasters, 
						CatFinalize};

metadata Cat_metadata = {"Cat", 
						sizeof(Cat), 
						&Animal_metadata, 
						&vtable_cat};

void CatCtor2(Cat *cat, char *color)
{
	AnimalCtor1((Animal *)cat);
	cat->colors = color;
	printf("Cat Ctor with color: %s\n", cat->colors);
}

void CatCtor1(Cat *cat)
{
	CatCtor2(cat, "black");
	printf("Cat Ctor\n");
	cat->num_masters = 2;
}

void CatStaticInitializers()
{
	if(!g_cat_flag)
	{
		printf("Static block Cat\n");
	}

	g_cat_flag = 1;
}

Cat *CreateCat(void *args)
{
	Cat *cat = ObjAlloc(&Cat_metadata);
	cat->animal.num_legs = 5;
	cat->animal.num_masters = 1;
	cat->num_masters = 5;
	CatStaticInitializers();
	AnimalInstanceInitializers();
	if((char *)args == NULL)
	{
		CatCtor1(cat);
	}
	else
	{
		CatCtor2(cat, (char *)args);
	}
	
	return cat;
}

/******* End of Class Cat ******/

/***** Start of Class LegendaryAnimal ******/

typedef struct LegendaryAnimal
{
	Cat cat;
} LegendaryAnimal;

void LegendarySayHello(void *args)
{
	(void)args;
	printf("Legendary Hello!\n");
}

char *LegendaryToString(void *args)
{
	char *buffer = malloc(sizeof(char) * 80);
	if(buffer == NULL)
	{
		return NULL;
	}

	sprintf(buffer, "LegendaryAnimal with ID: %d", ((Animal *)args)->ID);

	return buffer;
}

void LegendaryAnimalFinalize(void *args)
{
	(void)args;
	printf("finalize LegendaryAnimal with ID:%d", ((Animal *)args)->ID);
	InvokeMethod((Object *)args, FINALIZE, (LegendaryAnimal *)args);
}

vfunc_t vtable_LegendaryAnimal[] = {LegendarySayHello, 
									(void(*)(void *))LegendaryToString, 
									(void(*)(void *))getNumMasters, 
									LegendaryAnimalFinalize};

metadata LegendaryAnimal_metadata = {"LegendaryAnimal",
									 sizeof(LegendaryAnimal), 
									 &Cat_metadata, 
									 &vtable_LegendaryAnimal};

void LegendaryStaticInitializers()
{
	if(!g_legenderyanimal_flag)
	{
		printf("Static block Legendary Animal\n");
	}

	g_legenderyanimal_flag = 1;
}

void LegendaryCtor(LegendaryAnimal *leg)
{
	CatCtor1((Cat *)leg);
	printf("Legendary Ctor\n");
}

LegendaryAnimal *CreateLegendary()
{
	LegendaryAnimal *leg = ObjAlloc(&LegendaryAnimal_metadata);
	leg->cat.animal.num_legs = 5;
	leg->cat.animal.num_masters = 1;
	LegendaryStaticInitializers();
	AnimalInstanceInitializers();
	LegendaryCtor(leg);

	return leg;
}

/******* End of Class LegendaryAnimal ******/

/***** Start of Utility Functions ******/

void *ObjAlloc(metadata *md)
{
	Object *obj = (Object *)malloc(md->size);
	if(obj == NULL)
	{
		return NULL;
	}

	obj->class = md;

	return obj;
}

vfunc_t GetVirtualMethod(Object *obj, int index)
{
    return *((vfunc_t *)obj->class->vtable + index);
}

vfunc_t GetSuperMethod(metadata *curr_meta, int index)
{
    return (*(curr_meta->super_class->vtable))[index];
}

void InvokeMethod(Object *obj, int index, void *args)
{
	vfunc_t fp = *((vfunc_t *)obj->class->vtable + index);
	fp(args);
}

/******* End of Utility Functions ******/

void foo(Animal *animal)
{
	vfunc_t fp = GetVirtualMethod((Object *)animal, TO_STRING);
	printf("%s\n", ((char *(*)(void *))fp)(animal));
}

int main()
{
	Animal *animal = CreateAnimal();
	Dog *dog = CreateDog();
	Cat *cat = CreateCat(NULL);
	LegendaryAnimal *leg = CreateLegendary();
	Animal *array[5];
	int i = 0;
	vfunc_t fp = NULL;

	showCounter();
	printf("%d\n", animal->ID);
	printf("%d\n", dog->animal.ID);
	printf("%d\n", cat->animal.ID);
	printf("%d\n", leg->cat.animal.ID);
	
	array[0] = (Animal *)CreateDog();
	array[1] = (Animal *)CreateCat(NULL);
	array[2] = (Animal *)CreateCat("white");
	array[3] = (Animal *)CreateLegendary();
	array[4] = (Animal *)CreateAnimal();

	for (i = 0; i < NUM_ANIMALS; ++i)
	{
		InvokeMethod((Object *)array[i], SAY_HELLO, array[i]);
		fp = (GetVirtualMethod((Object *)array[i],GET_NUM_MASTERS));
		printf("%d\n", (((int (*)(void *))fp)(array[i])));
	}

	for (i = 0; i < NUM_ANIMALS; ++i)
	{
		foo(array[i]);
	}

	return 0;
}