/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 16/07/2019		*
*	 Reviewer: Inbar       		*
*								*
*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <math.h> /* pow */

#include "../include/dll.h" /* Dll header file */
#include "../include/hash.h" /* Hash header file */

struct dll
{
    struct dll_node *head;
    struct dll_node *tail;
};

struct hash
{
	int (*Compare)(const void *data, const void *key);
	size_t (*HashFunction)(void *key);
	size_t range;
	dll_t **table;
};

hash_t *HashCreate(int (*Compare)(const void *data, const void *key), size_t (*HashFunction)(void *key), const size_t range)
{
	hash_t *hash = NULL;
	int i = 0;

	assert (Compare);
	assert (HashFunction);
	assert (range > 0);

	hash = (hash_t *)malloc(sizeof(hash_t));
	if (!hash)
	{
		return NULL;
	}

	hash->Compare = Compare;
	hash->HashFunction = HashFunction;
	hash->range = range;

	hash->table = (dll_t **)malloc(sizeof(dll_t *) * range);
	if (!hash->table)
	{
		free(hash);

		return NULL;
	}

	for (; i < (int)range; ++i)
	{
		hash->table[i] = DLLCreate();
		if(hash->table[i] == NULL)
		{
			for(; i >= 0; --i)
			{
				DLLDestroy(hash->table[i]);
			}

			free(hash->table);
			free(hash);
		}
	}

	return hash;
}

void HashDestroy(hash_t *table)
{
	int i = 0;

	assert(table);

	for (; i < (int)table->range; ++i)
	{
		DLLDestroy(table->table[i]);
	}
	free(table->table);
	free(table);
}

int HashInsert(hash_t *table, const void *data)
{
	size_t key = 0;

	assert(table);
	assert(data);

	key = table->HashFunction((void *)data) % table->range;

	return (DLLEnd(table->table[key]) == DLLPushBack(table->table[key], (void *)data));
}

void HashRemove(hash_t *table, void *key)
{
	size_t hash_key = 0;
	void *data = 0;
	int res = 0;
	it_t current = NULL;

	assert(table);
	assert(key);

	hash_key = table->HashFunction((void *)key);
	current = DLLBegin(table->table[hash_key]);
	while (current)
	{
		data = DLLGetData(current);
		res = table->Compare(data , key);
		if(res == 1)
		{
			DLLPopFront(table->table[hash_key]);

			return ;
		}
	}
}

void *HashFind(const hash_t *table, void *key)
{
	size_t hash_key = 0;
	void *data = 0;
	int res = 0;
	it_t current = NULL;

	assert(table);
	assert(key);

	hash_key = table->HashFunction((void *)key) % table->range;
	current = DLLBegin(table->table[hash_key]);

	if(DLLEnd(table->table[hash_key]) == current)
	{
		return NULL;
	}

	while (current != DLLEnd(table->table[hash_key]))
	{
		data = DLLGetData(current);
		res = table->Compare(data , key);
		if(res == 1)
		{
			return data;
		}
		current = DLLNext(current);
	}

	return NULL;
}

size_t HashSize(const hash_t *table)
{
	int i = 0;
	size_t size = 0;

	assert(table);

	for (; i < (int)table->range; ++i)
	{
		size += DLLSize(table->table[i]);	
	}

	return size;
}

int HashIsEmpty(const hash_t *table)
{
	assert(table);

	return (0 == HashSize(table));
}

int HashForEach(hash_t *table, int (*act_f)(void *data, const void *params), const void *params)
{
	int i = 0;
	int status = 0;

	assert(table);

	for (; i < (int)table->range; ++i)
	{
		status = DLLForEach(DLLBegin(table->table[i]), DLLEnd(table->table[i]), act_f, params);	
		if(0 != status)
		{
			return 0;
		} 
	}

	return 1;
}

double HashLoad(hash_t *table)
{
	assert(table);

	return (HashSize(table) / table->range);
}

double HashSD(hash_t *table)
{
    double mid =  HashLoad(table);
    double sum = 0;
    size_t i = 0;

   	assert(table);
    
    for(; i< table->range; ++i)
    {
        sum += pow(DLLSize(table->table[i]) - mid, 2);
    }
    
    sum = sum / table->range;
    
    return sqrt(sum) / sqrt(table->range);
}