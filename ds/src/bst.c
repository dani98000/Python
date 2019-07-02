#include <stdlib.h>
#include <assert.h>

#include "../include/bst.h"

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

static int HowManyChildren(bst_it_t node);

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
	int flag = 0;
	bst_it_t iter= NULL;
	bst_it_t runner = bst->dummy.children[LEFT];
	bst_it_t runner_child = NULL;	
	bst_it_t runner_parent = NULL;		
	int side = 0;
	int res = 0;

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
	bst_it_t runner = bst->dummy.children[LEFT];	
	
	assert(NULL != bst);

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
	return (bst->dummy.children[LEFT] == NULL);
}

bst_it_t BSTPrev(bst_it_t node)
{
	bst_it_t res = InOrder(node, LEFT);

	return res;
}

bst_it_t BSTNext(bst_it_t node)
{
	return InOrder(node, RIGHT);
}

void *BSTGetData(bst_it_t node)
{
	return node->data;
}

void BSTRemove(bst_it_t node)
{
	int side = 0;
	bst_it_t successor = NULL;
	bst_it_t parent = NULL;
	
	parent = node->parent;
	
	if(HowManyChildren(node) == -1)
	{
		free(node);
		side = node == parent->children[RIGHT];	
		
		parent->children[side] = NULL;
		return;
	}
	else if(HowManyChildren(node) == 1)
	{
		node->data = node->children[RIGHT]->data;
		free(node->children[RIGHT]);
		parent->children[RIGHT] = NULL;
		return;
	}
	else if(HowManyChildren(node) == 0)
	{
		node->data = node->children[LEFT]->data;
		free(node->children[LEFT]);
		parent->children[LEFT] = NULL;
		
		return;
	}
	else if(HowManyChildren(node) == 2)
	{
		successor = BSTNext(node);
		parent = successor->parent;
		node->data = successor->data;
		free(successor);
		parent->children[LEFT] = NULL;
		return;
	}
}

size_t BSTCount(const bst_t *bst)
{
	size_t count = 0;
	bst_it_t runner = NULL;
	
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
	bst_it_t runner = bst->dummy.children[LEFT];
	int res = 0;
	
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

static int HowManyChildren(bst_it_t node)
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
