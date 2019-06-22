/*******************************************************************************
* Programmer: Eldad Carin
* Reviewer: 
* File: fsma code
* Date: 19-06-2019 13:29:42
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* EXIT_SUCCESS */

#include "fsma.h"

#define WORD (sizeof(size_t))
#define ONSET (sizeof(fsma_t))

struct fsma
{
	size_t next_free;
	size_t block_size;
	size_t n_blocks;
};                  

static size_t BrutoBlock(size_t block_size)   
{       
    if (WORD > block_size)
    {
        block_size = WORD;
    }
    
    if (0 != block_size % WORD)
    {
        block_size += WORD - (block_size % WORD);
    }    
    
    return block_size + WORD;
}

size_t FSMASuggestSize(size_t n_blocks, size_t block_size)
{  
    block_size = BrutoBlock(block_size);

    return block_size * n_blocks + ONSET;
}

fsma_t *FSMAInit(void *pool, size_t pool_size, size_t block_size)
{
    fsma_t *new_fsma = NULL;
    size_t *runner = NULL;
    size_t i = 0;
    size_t bruto_block = 0;
    size_t offset = 0;  
        
    assert(NULL != pool);
    
    bruto_block = BrutoBlock(block_size);
    new_fsma = (fsma_t *)pool;    
    
    new_fsma->block_size = block_size;
    new_fsma->n_blocks = (pool_size - ONSET) / bruto_block;
    new_fsma->next_free = ONSET;
       
    for (i = 0; i < new_fsma->n_blocks; ++i)
    {
        offset = ONSET + i * bruto_block;
        runner = (size_t *)((size_t)new_fsma + offset);
        *runner = (size_t)(offset + bruto_block);                                    
    }

    *runner = 0; 

    return new_fsma;
}

void *FSMAAlloc(fsma_t *fsma)
{
    size_t *current = NULL;
    
    assert(NULL != fsma);
    
    if (0 == fsma->next_free)
    {
        return NULL;
    }
     
    current = (size_t *)((size_t)fsma + fsma->next_free);
    fsma->next_free = *current;
    *current = (size_t)current - (size_t)fsma;
                                 
    return (void *)((size_t)current + WORD);        
}

void FSMAFree(void *block)
{
    size_t *offset = NULL;
    fsma_t *fsma = NULL;
    
    assert(NULL != block);
    
    offset = (size_t *)((size_t)block - WORD);
    fsma = (fsma_t *)((size_t)offset - *offset); 

    *offset = fsma->next_free;
    fsma->next_free = (size_t)offset - (size_t)fsma;            
}

size_t FSMACountFree(fsma_t *fsma)
{
    size_t *runner = NULL;
    size_t ctr = 0;
    
    assert(NULL != fsma);
    
    runner = (size_t *)((size_t)fsma + fsma->next_free);
    
    while (fsma != (fsma_t *)runner)
    {
        ++ctr;        
        runner = (size_t *)((size_t)fsma + *runner);
    }
    
    return ctr;    
}

