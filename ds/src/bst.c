/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 30/06/2019		*
*	 Reviewer: Ben           	*
*								*
*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h>/* assert */

#include "../include/bst.h" /* bst header */

enum children{NO_CHILDREN = -1, LEFT_CHILD, RIGHT_CHILD, TWO_CHILDREN};
enum side{LEFT, RIGHT};

struct bst_node
{
	void *data;
	bst_it_t parent;
	bst_it_t children[2];
};

struct bst
{
	struct bst_node dummy;
	cmp_f compare;
	void *params;
};

static bst_it_t InOrder(bst_it_t iter, int side);
static int ChildrenTest(bst_it_t node);

static bst_it_t BSTCreateNode(void *data, bst_it_t parent, bst_it_t left, bst_it_t right)
{
	bst_it_t node = (bst_it_t)malloc(sizeof(struct bst_node));
	
	if(NULL == node)
	{
		free(node);
		return NULL;
	}
	
	node->data = (void *)data;
	node->parent = parent;
	node->children[LEFT] = left;
	node->children[RIGHT] = right;
	
	return node;
}

bst_t *BSTCreate(cmp_f compare, const void *params)
{
	bst_t *bst = (bst_t *)malloc(sizeof(bst_t));
	
	if(NULL == bst)
	{
		free(bst);
		return NULL;
	}
	
	bst->dummy.data = (void *)0xDEADBEEF;
	bst->dummy.parent = NULL;
	bst->dummy.children[LEFT] = NULL;
	bst->dummy.children[RIGHT] = NULL;
	bst->compare = compare;
	bst->params = (void *)params;
	
	return bst;
}

bst_it_t BSTInsert(bst_t *bst, void *data)
{
	bst_it_t iter= NULL;
	bst_it_t runner_child = NULL;	
	bst_it_t runner_parent = NULL;
	bst_it_t runner = NULL;		
	int flag = 0;
	int side = 0;
	int res = 0;
	
	assert(NULL != bst);	
	
	runner = bst->dummy.children[LEFT];

	if(BSTIsEmpty(bst))
	{
		iter = BSTCreateNode(data, (bst_it_t)bst, NULL, NULL);
		bst->dummy.children[LEFT] = iter;
		
		return iter;
	}
	
	while(runner != NULL)
	{
		runner_parent = runner;
		res = bst->compare(runner->data, data, NULL);
		if(res > 0)
		{
			runner = runner->children[LEFT];
			flag = LEFT;
		}	
		else if(res < 0)
		{	
			runner = runner->children[RIGHT];
			flag = RIGHT;
		}
		else
		{
			return (bst_it_t)bst;
		}
	}
	
	iter = BSTCreateNode(data, runner_parent, NULL, NULL);
	runner_parent->children[flag] = iter;
	
	return iter;
} 

bst_it_t BSTBegin(const bst_t *bst)
{
	bst_it_t runner = NULL;	
	
	assert(NULL != bst);

	runner = bst->dummy.children[LEFT];

	while(runner->children[LEFT] != NULL)
	{
		runner = runner->children[LEFT];
	}
	
	return runner;
}

bst_it_t BSTEnd(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (bst_it_t)bst;
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (bst->dummy.children[LEFT] == NULL);
}

bst_it_t BSTPrev(bst_it_t node)
{
	assert(NULL != node);
	
	return InOrder(node, LEFT);
}

bst_it_t BSTNext(bst_it_t node)
{
	assert(NULL != node);

	return InOrder(node, RIGHT);
}

void *BSTGetData(bst_it_t node)
{
	assert(NULL != node);

	return node->data;
}

void BSTRemove(bst_it_t node)
{
	int side = 0;
	int res = 0;
	bst_it_t successor = NULL;
	bst_it_t parent = NULL;
	
	assert(NULL != node);
	
	parent = node->parent;
	res = ChildrenTest(node);
	if(res == NO_CHILDREN)
	{
		free(node);
		side = node == parent->children[RIGHT];		
		parent->children[side] = NULL;
	}
	else if(res == TWO_CHILDREN)
	{
		successor = BSTNext(node);
		parent = successor->parent;
		node->data = successor->data;
		res = ChildrenTest(successor);	
		if(res == RIGHT_CHILD)
		{
			successor->data = successor->children[RIGHT]->data;
			free(successor->children[RIGHT]);
			successor->children[RIGHT] = NULL;
		}	
	}
	else
	{
		node->data = node->children[res]->data;
		free(node->children[res]);
		node->children[res] = NULL;
	}	
}

size_t BSTCount(const bst_t *bst)
{
	size_t count = 0;
	bst_it_t runner = NULL;
	
	assert(NULL != bst);
	
	if(BSTIsEmpty(bst))
	{
		return 0;
	}
	
	runner = BSTBegin(bst);
	
	while(runner != (bst_it_t)bst)
	{
		++count;
		runner = BSTNext(runner);
	}
	
	return count;
}

bst_it_t BSTFind(const bst_t *bst, const void *data)
{
	bst_it_t runner = NULL;
	int res = 0;
	
	assert(NULL != bst);
	
	runner = bst->dummy.children[LEFT];
	
	while(runner != NULL)
	{
		res = bst->compare(runner->data, data, NULL);
		if(res == 0)
		{
			return runner;
		}
		else if(res > 0)
		{
			runner = runner->children[LEFT];
		}	
		else if(res < 0)
		{	
			runner = runner->children[RIGHT];
		}
	}
	return (bst_it_t)bst;
}

int BSTForEach(bst_it_t from, bst_it_t to, act_f action, const void *args)
{
	bst_it_t current = NULL;
	int status = 0;
	
	assert(NULL != from && NULL != to && action != NULL);
	
	for(current = from; current != to ; current = BSTNext(current))
	{
		status = (action)(current->data, args);
		if(0 != status)
		{
			return status;
		} 
	}
	
	return 0;
}

void BSTDestroy(bst_t *bst)
{
	bst_it_t parent = NULL;
	bst_it_t root = NULL;
	
	assert(NULL != bst);
	
	root = bst->dummy.children[LEFT];
	while(parent != BSTEnd(bst))
	{
        if(root->children[LEFT]) 
        {
            root = root->children[LEFT];
        } 
        else if (root->children[RIGHT]) 
        {
            root = root->children[RIGHT];
        } 
        else 
        {
            parent = root->parent;
            free(root);
                         
            if(parent->children[LEFT] == root)
            {
                parent->children[LEFT] = NULL;
            }
            else if (NULL == parent->children[LEFT] && parent->children[RIGHT] == root)
            {
                parent->children[RIGHT] = NULL;
            }
            root = parent;
        }
    }
    free(bst);
}	

static int ChildrenTest(bst_it_t node)
{
	if(node->children[LEFT] == NULL && node->children[RIGHT] == NULL)
	{
		return -1;
	}
	else if(node->children[LEFT] != NULL && node->children[RIGHT] != NULL)
	{
		return 2;
	}
	else if(node->children[LEFT])
	{
		return 0;
	}
	else if(node->children[RIGHT])
	{
		return 1;
	}
}

static bst_it_t InOrder(bst_it_t iter, int side)
{
	bst_it_t iter_parent = NULL;
	bst_it_t child = NULL;
	int other_side = side == RIGHT ? LEFT : RIGHT;
	
	iter_parent = iter->parent;
	if(iter->children[side] == NULL)
	{
		while(iter_parent->children[side] == iter)
		{
			iter = iter->parent;
			iter_parent = iter_parent->parent;
			if(iter_parent == NULL)
			{
				break;
			}
		}
		
		return iter_parent;
	}
	else
	{
		child = iter->children[side];
		while(child->children[other_side] != NULL)
		{
			child = child->children[other_side];
		}
		
		return child;
	}
}
