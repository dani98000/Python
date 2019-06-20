/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 02/06/19                                *
*   Description: Circular Buffer - Implementation *
*                                                 *
**************************************************/
#include <stdlib.h> /* malloc */
#include <errno.h>  /* errno  */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "../../include/CBUF/cbuf.h"

struct CBUF
{
	size_t capacity;
	size_t size;        /* distance frome read to write */
	size_t read_offset; /* distance from buff start to read */
	void *buff;
};

cbuf_t *CBUFCreate(size_t nbytes)
{
	cbuf_t *new_cbuf = NULL;

	assert(nbytes > 0);

	if(0 == nbytes)
	{
		return NULL;
	}

	new_cbuf = (cbuf_t *)malloc(sizeof(cbuf_t));
	if(NULL == new_cbuf)
	{
		return NULL;
	}

	new_cbuf->capacity = nbytes;
	new_cbuf->size = 0;
	new_cbuf->read_offset = 0;

	new_cbuf->buff = malloc(nbytes); /* allocate capacity bytes */
	if(NULL == new_cbuf->buff)
	{
		free(new_cbuf);
		return NULL;
	}

	return new_cbuf;
}

size_t CBUFRead(cbuf_t *cbuf, void *data, size_t nbytes)
{
	size_t segment_a = 0, segment_b = 0;
	size_t initial_size = cbuf->size;

	if(nbytes >= cbuf->size) /* out of data before reading ends */
	{
		segment_a = cbuf->size;
		errno = ENODATA;
		cbuf->size = 0;
	}
	else /* has enough data to read */
	{
		cbuf->size -= nbytes;
		segment_a = nbytes;
	}

	if(cbuf->read_offset + nbytes > cbuf->capacity) /* reading wraps around */
	{
		segment_b = (cbuf->read_offset + nbytes) % cbuf->capacity;
		segment_a -= segment_b;
	
		/* read first chunk */
		memcpy(data, (char *)cbuf->buff + cbuf->read_offset, segment_a);

		cbuf->read_offset = segment_b;

		/* read second chunck */
		memcpy((char *)data + segment_a, (char *)cbuf->buff, segment_b);
	}
	else /* reading does not wrap around */
	{
		memcpy(data, (char *)cbuf->buff + cbuf->read_offset, segment_a);
		cbuf->read_offset = (cbuf->read_offset + segment_a) % cbuf->capacity;
	}

	return (initial_size - cbuf->size);
}

size_t CBUFWrite(cbuf_t *cbuf, const void *data, size_t nbytes)
{
	size_t segment_a = 0, segment_b = 0;

	assert(NULL != data);
	assert(NULL != cbuf);

	if(cbuf->size + nbytes >= cbuf->capacity) /* overflow */
	{
		errno = EOVERFLOW;
		/* gets rid of overflow */
		nbytes -= (cbuf->size + nbytes) % cbuf->capacity; 
	}

	segment_a = nbytes;

	/* is there a wrap around? */
	if(cbuf->read_offset + cbuf->size + nbytes > cbuf->capacity) 
	{
		segment_b = (cbuf->read_offset + cbuf->size + nbytes) % cbuf->capacity;
		segment_a -= segment_b;
	}

	/* copy segment a*/
	memcpy((char *)cbuf->buff + cbuf->read_offset + cbuf->size, data,
		segment_a);

	/* copy segment b */
	memcpy(cbuf->buff, (char *)data + segment_a, segment_b);

	cbuf->size += nbytes;

	return nbytes;
}

size_t CBUFFreeSpace(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);

	return (cbuf->capacity - cbuf->size);
}

int CBUFIsEmpty(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);
	
	return (0 == cbuf->size);
}

void CBUFDestroy(cbuf_t *cbuf)
{
	assert(NULL != cbuf && NULL != cbuf->buff);

	free(cbuf->buff);
	free(cbuf);
}

size_t CBUFCapacity(const cbuf_t *cbuf)
{
	return cbuf->capacity;
}






