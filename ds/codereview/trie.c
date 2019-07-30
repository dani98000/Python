/*******************************************
 **         Author: Mishel Liberman       **
 **         Reviewer: Sasha Limarev       **
 **         Date: 29.07.19                **
 *******************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <math.h> /* pow */

#include "trie.h" 

#define OFFSET 1
#define BITS 32

typedef struct node node_t;

struct node
{
    int is_full;
    node_t *children[2];
};

struct trie
{
    size_t num_of_bits;
    node_t *root;
};

static node_t *NodeCreate()
{
    node_t *node = malloc(sizeof(*node));
    if (!node)
    {
        return NULL;
    }
        
    node->children[0] = NULL;
    node->children[1] = NULL;
    node->is_full = 0;
    
    return node;
}

trie_t *TrieCreate(uint32_t num_of_bits) /* inclusive */
{
    trie_t *trie = malloc(sizeof(*trie));
    if (!trie)
    {
        return NULL;
    }

    assert(num_of_bits > 0);
    
    trie->root = NodeCreate();
    if (!trie->root)
    {
        free(trie);
        trie = NULL;
        
        return NULL;
    }
    
    trie->num_of_bits = num_of_bits;

    return trie;
}

static void RecurDestroyNodes(node_t *node)
{
    if (NULL == node)
    {
        return;
    }
    else
    {
        RecurDestroyNodes(node->children[0]);
        RecurDestroyNodes(node->children[1]);
    }
    
    free(node);
    node = NULL;
}

void TrieDestroy(trie_t *trie)
{
    assert(trie);
    
    RecurDestroyNodes(trie->root);
    
    free(trie);
    trie = NULL;
}

static enum status_trie RecurInsert(node_t *node, uint32_t ip, uint32_t shift)
{
    int index = ip >> shift & 0x1;
    enum status_trie status = SUCCESS;

    if (!node->children[index])
    {
        node->children[index] = NodeCreate();
        if (!node->children[index])  
        {

            return M_FAIL; /* malloc failure */
        }  

        if (shift == 0) /* last bit created */
        {
            node->children[index]->is_full = 1;

            if (node->children[!index] && node->children[!index]->is_full == 1)
            {
                node->is_full  = 1;
            }

            return SUCCESS;
        }
    }
    else if (0 == shift)        
    {
        return FAILURE; /* already in use */
    }

    status = RecurInsert(node->children[index], ip, shift - OFFSET);

    if (node->children[0] && node->children[0]->is_full == 1
        && node->children[1] &&  node->children[1]->is_full == 1)
    {
        node->is_full  = 1;
    }

    return status;
} 
    
enum status_trie TrieInsert(trie_t *trie, uint32_t ip)
{
    assert(trie);

    return RecurInsert(trie->root, ip, trie->num_of_bits - OFFSET);
}

static int FindSuccesor(const node_t *node, uint32_t shift, 
                         uint32_t *ip)
{
    int next_index = 0;

    if (!node->children[0] || node->children[0]->is_full)
    {
        if (!node->children[1])
        {
            *ip += (pow(2, shift) * 1);

            return 0;
        }
        else if (node->children[1]->is_full)
        {
            return 1;
        }

        next_index = 1;
    }

    if (0 == FindSuccesor(node->children[next_index], shift - OFFSET, ip))
    {
        *ip += (pow(2, shift) * next_index);

        return 0;
    }

    return 1;
}

uint32_t TrieNextFreeIp(const trie_t *trie)
{
    int shift = trie->num_of_bits - OFFSET;
    uint32_t new_ip = 0;
    uint32_t mask = 0;

    mask = ~0x0 << trie->num_of_bits; 

    if (0 == FindSuccesor(trie->root, shift, &new_ip))
    {
        if (new_ip == !mask)
        {
            return 0;
        }

        return (new_ip);
    }

    return mask;
}

static found_t IsAvailable(const node_t *node, uint32_t ip, uint32_t shift)
{
    int index = ip >> shift & 0x1;
    
    if (!node->children[index])
    {
        return TRUE; 
    }   

    if (0 == shift)
    {
        return FALSE; 
    } 

    if (node->is_full)
    {
        return FALSE; 
    }

    return IsAvailable(node->children[index], ip, shift - OFFSET);
}

found_t TrieFind(const trie_t *trie, uint32_t ip)
{
    assert(trie);

    return IsAvailable(trie->root, ip, trie->num_of_bits - OFFSET);
}

uint32_t RecurTrieCount(const node_t *node, int max_height, int current_height)
{
    if (!node)
    {
        return 0;
    }

    if (!node->children[0] && !node->children[1])
    {
        if (max_height == current_height)
        {
            return 1;
        }
    }

    return (RecurTrieCount(node->children[0], max_height, current_height + 1)
           + RecurTrieCount(node->children[1], max_height, current_height + 1));
}

uint32_t TrieCount(const trie_t * trie)
{
    assert(trie);

    return RecurTrieCount(trie->root, trie->num_of_bits, 0);
}

enum status_trie RecurRemove(node_t *node, uint32_t ip, uint32_t shift)
{
    int index = ip >> shift & 0x1;
    enum status_trie status = SUCCESS;

    if (!node->children[index])
    {
        return FAILURE;
    }

    if (node->children[index] && shift == 0)
    {
        free(node->children[index]);
        node->children[index] = NULL;
        node->is_full = 0;

        return SUCCESS;
    }

    if (SUCCESS == RecurRemove(node->children[index], ip, shift - OFFSET))
    {
        node->is_full = 0;
    }

    return status;
}

enum status_trie TrieRemove(trie_t *trie, uint32_t ip)
{
    assert(trie);

    return RecurRemove(trie->root, ip, trie->num_of_bits - OFFSET);
}

size_t TrieNumOfBits(const trie_t *trie)
{
    assert(trie);

    return trie->num_of_bits;
}

