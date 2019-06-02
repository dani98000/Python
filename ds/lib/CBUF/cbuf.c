#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../include/CBUF/cbuf.h"

struct CBUF
{
    size_t capacity;
    size_t size;
    size_t read_offset;
    void *buff;
};

cbuf_t *CBUFCreate(size_t nbytes)
{
    cbuf_t *cbuf = malloc(sizeof(cbuf_t));
    assert(nbytes>0);
	if(NULL == cbuf)
	{
		return NULL;
	}
	cbuf->buff = (void *)malloc(nbytes);
	if (NULL == cbuf->buff)
	{
		return NULL;
	}
	cbuf->capacity = nbytes;
	cbuf->size = 0;
	cbuf->read_offset = 0;
    return cbuf;
}

void CBUFDestroy(cbuf_t *cbuf)
{
	free(cbuf->buff);
	free(cbuf);
}

size_t CBUFRead(cbuf_t *cbuf, void *data, size_t nbytes)
{
	size_t count = 0;
	while((char *)(void*)cbuf->size > (char*)cbuf->read_offset)
	{
		*(char *)data=*((char*)cbuf->buff + (char)cbuf->read_offset);
		++(cbuf->read_offset);
		++count;
	}
	return count;
}

size_t CBUFWrite(cbuf_t *cbuf, const void *data, size_t nbytes)
{
	size_t count = 0;
	void *dest = NULL;

    if (cbuf->size + 1 == cbuf->read_offset)
    { 											
        return 1;
	}
	
	dest = (char *)(cbuf->buff) + cbuf->size;
	if(nbytes > cbuf->capacity - cbuf->size)
	{
		nbytes = cbuf->capacity - cbuf->size;
	}	
	memcpy(dest, data, nbytes);
	cbuf->size +=nbytes;
	return nbytes;
}
/*
int CBUFIsEmpty(const cbuf_t *cbuf);
size_t CBufFreeSpace(cbuf_t *cbuf);
size_t CBufCapacity(cbuf_t *cbuf);*/
