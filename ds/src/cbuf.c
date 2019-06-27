/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Mishel          	*
*								*
*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <errno.h>  /* perror */

#include "../include/cbuf.h" /* header file */

struct CBUF
{
    size_t capacity;
    size_t size;
    size_t read_offset;
    void *buff;
};

cbuf_t *CBUFCreate(size_t nbytes)
{
	cbuf_t *cbuf = NULL;
    
    assert(nbytes > 0);
    
    if(0== nbytes)
    {
		return NULL;
	}	
    cbuf = (cbuf_t *)malloc(sizeof(cbuf_t));        
	if(NULL == cbuf)
	{
		return NULL;
	}
	
	
	cbuf->buff = (void *)calloc(nbytes,sizeof(char));
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
	assert(NULL != cbuf && NULL != cbuf->buff);
	
	free(cbuf->buff);
	free(cbuf);
}

size_t CBUFRead(cbuf_t *cbuf, void *data, size_t nbytes)
{
	size_t count = 0;
	
	assert(NULL != cbuf);
	assert(NULL != data);
	
    while (cbuf->size > 0 && nbytes > 0)
	{
  		((char *)data)[count] = ((char*)cbuf->buff)[cbuf->read_offset];
   		 ++cbuf->read_offset;
   		 --cbuf->size;
   		 ++count;
   		 --nbytes;
   		 
    	if (cbuf->read_offset == cbuf->capacity)
		{
	        cbuf->read_offset = 0;
		}
	}

	if(CBUFIsEmpty(cbuf))
	{
		errno = ENODATA;
	}

    return count;
}

size_t CBUFWrite(cbuf_t *cbuf, const void *data, size_t nbytes)
{
	size_t count = 0;
	
	assert(NULL != cbuf);
	assert(NULL != data);
	
	
	while(CBUFFreeSpace(cbuf) > 0 && nbytes > 0)
	{
    	((char*)cbuf->buff)[(cbuf->size + cbuf->read_offset) % cbuf->capacity] 
			= ((char *)data)[count];
    	++cbuf->size;
    	--nbytes;
    	++count;
	}
	if(0 == CBUFFreeSpace(cbuf))
    {
		errno = EOVERFLOW;
    }

    return count;
}

int CBUFIsEmpty(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);	

	return (0 == cbuf->size);
}

size_t CBUFFreeSpace(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);

	return (cbuf->capacity - cbuf->size);
}

size_t CBUFCapacity(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);

	return (cbuf->capacity);
}
