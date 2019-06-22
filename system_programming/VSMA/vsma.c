#include <stddef.h>
#include <assert.h>
#include  <stdio.h>
#include "vsma.h"

#define MAGIC_NUMBER 0x80808080
#define WORD 8
#define METADATA_SIZE (sizeof(blk_header_t))

struct vsma 
{
    void *pool;
};


typedef struct blk_header
{
   long block_size;
	#ifdef DNDEBUG
    long magic_num;
	#endif
} blk_header_t;

static void defrag(blk_header_t *current, blk_header_t *next)
{	
	size_t temp = 0;
	temp = next->block_size;
	next = current;
	current->block_size = current->block_size + temp + sizeof(blk_header_t);
	#ifdef DNDEBUG
	current->magic_num = MAGIC_NUMBER;
	#endif 
}

static blk_header_t *UpdateNext(blk_header_t *current)
{
	blk_header_t *next = NULL;
	
	if(current->block_size < 0)
	{
		next = (blk_header_t *)((char *)current + (current->block_size * -1) + sizeof(blk_header_t));
	}
	else if (current->block_size > 0)
	{
		next = (blk_header_t *)((char *)current + current->block_size + sizeof(blk_header_t));
	}
	return next;
}

static size_t GetAligned(size_t block_size)
{
	return(WORD * (block_size / WORD) + (((block_size % WORD) == 0) ? 0 : WORD));
}

/* Initiates allocation manager */
vsma_t *VSMAInit(void *pool, size_t pool_size)
{
	blk_header_t *start = NULL;
	blk_header_t *end = NULL;
	
	assert(NULL != pool);
	
	start = (blk_header_t *)pool;
	end = (blk_header_t *)((char *)pool + pool_size - sizeof(blk_header_t));
	end = (blk_header_t *)((size_t)end - ((size_t)end % WORD));
	start->block_size = (char *)end - (char *)start - METADATA_SIZE;
	end->block_size = 0;
	#ifdef DNDEBUG
	start->magic_num = MAGIC_NUMBER;
	end->magic_num = MAGIC_NUMBER;
	#endif
	
	return((vsma_t *)start);
}

void *VSMAAlloc(vsma_t *vsma, size_t block_size)
{
	blk_header_t *current = (blk_header_t *)vsma;
	blk_header_t *next = NULL;
	size_t temp = 0;
	block_size = GetAligned(block_size);
	
	
	if(current->block_size < 0)
	{
		next = (blk_header_t *)((char *)current + (current->block_size * -1) + sizeof(blk_header_t));
	}
	else if (current->block_size > 0)
	{
		next = (blk_header_t *)((char *)current + current->block_size + sizeof(blk_header_t));
	}
		
	while(current->block_size < (long)(block_size + sizeof(blk_header_t)) && 0 != current->block_size)
	{
		next = UpdateNext(current);
		if(current->block_size > 0 && next->block_size > 0)
		{
			defrag(current, next); /*Handles defragmentation if needed and updates 'next' */
		}	
		if(current->block_size > (long)(block_size + sizeof(blk_header_t)))
		{
			next = (blk_header_t *)((char *)current + block_size + sizeof(blk_header_t));
			temp = current->block_size;
			current->block_size = -1 * block_size;
			#ifdef DNDEBUG
			current->magic_num = MAGIC_NUMBER;
			next->magic_num = MAGIC_NUMBER;
			#endif
			next->block_size = temp + current->block_size -  sizeof(blk_header_t);
	
			return (vsma_t *)((char *)current + sizeof(blk_header_t));
		}	
		current = next;					
	}
	
	if(current->block_size != 0)
	{
		next = (blk_header_t *)((char *)current +block_size + sizeof(blk_header_t));
		temp = current->block_size;
		current->block_size = -1 * block_size;
		next->block_size = temp + current->block_size - sizeof(blk_header_t);
		#ifdef DNDEBUG
		current->magic_num = MAGIC_NUMBER;
		next->magic_num = MAGIC_NUMBER;
		#endif
	
		return (vsma_t *)((char *)current + sizeof(blk_header_t));
	}
	else
	{
		return NULL;
	}
}

void VSMAFree(void *block)
{
	assert(0 > *(long *)((char *)block - 16));
	#ifdef DNDEBUG
	assert(0x80808080 == (*(long *)((char *)block - 8)));
	#endif

	((blk_header_t *)((char *)block - 16))->block_size *= -1;
}

size_t VSMACount(vsma_t *vsma)
{
	size_t sum = 0;
	blk_header_t *next = NULL;
	blk_header_t *current = NULL;
	
	assert(NULL != vsma);
			
	current = (blk_header_t *)vsma;
	while(current->block_size != 0)
	{
		next = UpdateNext(current);
		if(current->block_size > 0 && next->block_size > 0)
		{	
			defrag(current, next); /*Handles defragmentation if needed and updates 'next' */
			continue; 					
		}
		if(current->block_size > 0)
		{
			sum += current->block_size;
			current = (blk_header_t *)((char *)current + current->block_size + sizeof(blk_header_t));
		}
		else
		{
			current = (blk_header_t *)((char *)current + current->block_size * -1 + sizeof(blk_header_t));
		}					
	}
	
	return sum;
}

size_t VSMAFindLargestFree(vsma_t *vsma)
{
	size_t max = 0;
	blk_header_t *next = NULL;
	blk_header_t *current = NULL;
	
	assert(NULL != vsma);
			
	current = (blk_header_t *)vsma;
	while(current->block_size != 0)
	{
		next = UpdateNext(current);
		if(current->block_size > 0 && next->block_size > 0)
		{	
			defrag(current, next); /*Handles defragmentation if needed and updates 'next' */
			continue; 					
		}
		if(current->block_size > 0)
		{
			if(current->block_size > (long)max)
			{
				max = current->block_size;
			}
			current = (blk_header_t *)((char *)current + current->block_size + sizeof(blk_header_t));
		}
		else
		{
			current = (blk_header_t *)((char *)current + current->block_size * -1 + sizeof(blk_header_t));
		}					
	}
	
	return max;
}
