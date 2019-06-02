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

/*size_t CBUFRead(cbuf_t *cbuf, void *data, size_t nbytes)
{
	size_t count = 0;
	while(size+1 != read_offset)
	{
		++count;
	}
}*/

size_t CBUFWrite(cbuf_t *cbuf, const void *data, size_t nbytes)
{
	int next;
	size_t count = 0;
	void *dest = NULL;
    next = cbuf->size + 1;  // next is where head will point to after this write.
    
    if (next >= cbuf->capacity)
    {
        next = 0;
	}
	
    if (next == cbuf->read_offset)
    { 											 // if the size + 1 == off_set, circular buffer is full
        return NULL;
	}
	
    c->head = next;             // head to next data offset.
	dest = (char *)(cbuf->buff) + cbuf->size;
	memcpy(dest, data, nbytes);
	while(cbuf->size+1 < cbuf->read_offset)
	{
		++count;
	}
	cbuf->size = next;
	return count;
}
/*
int CBUFIsEmpty(const cbuf_t *cbuf);
size_t CBufFreeSpace(cbuf_t *cbuf);
size_t CBufCapacity(cbuf_t *cbuf);*/
