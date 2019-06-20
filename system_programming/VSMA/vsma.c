#include <stddef.h>
#include <assert.h>
#include "vsma.h"

#define MAGIC_NUMBER 0x80808080
#define WORD 8

struct vsma 
{
    void *pool;
};


typedef struct blk_header
{
    long block_size;

    long magic_num;
   
}blk_header_t;

static size_t frag(vsma_t vsma)
{
	blk_header_t *current = (blk_header_t *)vsma;
	blk_header_t *current_next = NULL;
	size_t counter = 0;
	
	while(current->block_size != 0)
	{
		current_next = (char *)currnet + current->block_size + sizeof(blk_header_t);
		if(current->block_size > 0 && current_next->block_size > 0)
		{
			current->block_size += current_next->block_size +sizeof(blk_header_t);
		}
		else
		{
			current = current_next;
		}
	}
	
	return counter;
}

static size_t GetAligned(size_t block_size)
{
	return(WORD * (block_size / WORD) + (((block_size % WORD) == 0) ? 0 : WORD) + sizeof(blk_header_t));
}

/* Initiates allocation manager */
vsma_t *VSMAInit(void *pool, size_t pool_size)
{
	blk_header_t *vsma = NULL;
	blk_header_t *last_metadata = NULL;
	
	assert(NULL != pool);
	
	vsma = (blk_header_t *)pool;
	vsma->block_size = pool_size - 2 * sizeof(blk_header_t);
	vsma->magic_num = MAGIC_NUMBER;
	last_metadata = (blk_header_t *)((char *)pool + pool_size -sizeof(blk_header_t));
	last_metadata->block_size = 0;
	last_metadata->magic_num = MAGIC_NUMBER;
	
	return((vsma_t *)vsma);
}

void *VSMAAlloc(vsma_t *vsma, size_t block_size)
{
	blk_header_t *current = (blk_header_t *)vsma;
	block_size = GetAligned(block_size)
	while(current->block_size < block_size + sizeof(blk_header_t) || current->block_size != 0)
	{
		current = (char *)currnet + current->block_size + sizeof(blk_header_t);
		if()					
	}
	return vsma;
}

/*void VSMAFree(void *block);

size_t VSMACount(vsma_t *vsma);

size_t VSMAFindLargestFree(vsma_t *vsma);*/
