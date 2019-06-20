/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Eldad        	*
*								*
*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "fsma.h" /* Fixed Size Memory Allocator header */

#define WORD sizeof(size_t)

struct fsma
{
	size_t next_free;
	size_t block_size;
	size_t n_blocks;
};

static size_t GetBlockSize(size_t block_size)
{
	return(WORD * (block_size / WORD) + (((block_size % WORD) == 0) ? 0 : WORD) + WORD);
}

size_t FSMASuggestSize(size_t n_blocks, size_t block_size)
{
	block_size = GetBlockSize(block_size);
	
	return(sizeof(fsma_t) + block_size * n_blocks);
}

fsma_t *FSMAInit(void *pool, size_t pool_size, size_t block_size)
{

	size_t base_offset = sizeof(fsma_t);
	char *runner = NULL;
	fsma_t *new_fsma = NULL;
	
	assert(NULL != pool && pool_size > 32);
	
	runner = (char *)pool + base_offset;
	new_fsma = (fsma_t *)pool;
	
	new_fsma->block_size = block_size;
	block_size = GetBlockSize(block_size);

	new_fsma->n_blocks = (pool_size - sizeof(fsma_t)) / block_size;
	new_fsma->next_free = sizeof(fsma_t); 	
	
	while((size_t)((char *)runner - (char *)pool) < pool_size)
	{
		*runner = (runner - (char *)pool) + block_size;
		runner += block_size;
	}
	
	*(size_t *)((char *)pool + pool_size - block_size) = 0;
	
	return pool;
}

void *FSMAAlloc(fsma_t *fsma)
{
	void *free_block = NULL;
	char *runner = NULL;
	size_t 	block_size = 0;
	int temp = 0;
	
	assert(NULL != fsma);
	
	block_size = GetBlockSize(block_size);
	free_block = (char *)fsma + fsma->next_free + WORD;
	runner = (char *)fsma + fsma->next_free;
	
	temp = fsma->next_free;
	fsma->next_free = *((size_t *)((char *)free_block - WORD));
	*(size_t *)runner = temp;
	
	return free_block; 
}

void FSMAFree(void *block)
{
	int temp = 0;
	char *runner = NULL;
	
	assert(NULL != block);
	
	runner = (char *)block - *(size_t *)((char *)block - WORD) - WORD;
	temp = *runner;
	*runner = *(size_t *)((char *)block - WORD);
	*(size_t *)((char *)block - WORD) = temp;
}

size_t FSMACountFree(fsma_t *fsma)
{
	char *runner = (char *)fsma + fsma->next_free;
	size_t 	block_size = 0;
	size_t 	count = 0;
	
	assert(NULL != fsma);
	
	block_size = GetBlockSize(block_size);
	
	while((fsma_t *)runner != fsma)
	{
		runner = (char *)fsma + *(size_t *)runner;
		++count;
	}

	return count;
}
