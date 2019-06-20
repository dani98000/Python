/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 19/06/19                                *
*   Description: Fixed Size Memory Allocator      *
*                                                 *
**************************************************/
#include <assert.h> /* assert */

#include "fsma.h"   /* FSMA header file */

#define WORD (sizeof(size_t))
#define METADATA_SIZE WORD
#define FSMA_SIZE (sizeof(fsma_t))

struct fsma
{
	size_t next_free;
	size_t block_size;
	size_t n_blocks;
};

static size_t GetBlockSize(size_t block_size);

size_t FSMASuggestSize(size_t n_blocks, size_t block_size)
{
	return FSMA_SIZE + (GetBlockSize(block_size) + METADATA_SIZE) * n_blocks;
}

fsma_t *FSMAInit(void *pool, size_t pool_size, size_t block_size)
{
	size_t n_blocks = 0, i = 0, offset = 0;
	char *runner = NULL;
	
	assert(NULL != pool && pool_size > 32);
	
	block_size = GetBlockSize(block_size);
	n_blocks = (pool_size - FSMA_SIZE) / (block_size + METADATA_SIZE);
	offset = FSMA_SIZE;
	
	((fsma_t *)pool)->block_size = block_size;
	((fsma_t *)pool)->n_blocks = n_blocks;
	((fsma_t *)pool)->next_free = offset; 
	
	/* the address of the first metadata */
	runner = (char *)pool + offset;
	--n_blocks;
	
	for(; i < n_blocks; ++i)
	{
		offset += (block_size + METADATA_SIZE);
		*(size_t *)runner = offset;
		runner += (block_size + METADATA_SIZE); /* get to the next metadata */
	}
	
	/* set the next of the last metadata is NULL */
	*(size_t *)runner = (size_t)NULL; 
	
	return (fsma_t *)pool;
}

void *FSMAAlloc(fsma_t *fsma)
{
	void *next_free = NULL;
	
	assert(NULL != fsma);
	
	next_free = (void *)((size_t)fsma + fsma->next_free);
	fsma->next_free = *(size_t *)next_free;
	*(size_t *)next_free = (size_t)fsma;
	
	return ((size_t *)next_free + 1);
}

void FSMAFree(void *block)
{
	size_t next_free = 0;
	fsma_t *fsma = NULL;
	
	assert(NULL != block);
	
	block = (size_t *)block - 1; /* move to the metadata */
	
	/* read the address of fsma from the block's metadata */
	fsma = (fsma_t *)(*(size_t *)block);	
	next_free = fsma->next_free;
	fsma->next_free = (char *)block - (char *)fsma;
	*(size_t *)block = next_free;
}

size_t FSMACountFree(fsma_t *fsma)
{
	size_t count = 0;
	size_t *runner = NULL;
	
	assert(NULL != fsma);
	
	runner = (size_t *)((size_t)fsma + fsma->next_free);
	
	while((size_t *)fsma != runner)
	{
		++count;
		runner = (size_t *)((size_t)fsma + *runner);
	}
	
	return count;
}

static size_t GetBlockSize(size_t block_size)
{
	return block_size + (WORD - (block_size % WORD)) % WORD;
}
