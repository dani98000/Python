/*******************************************************************
Author  : Sandra.Hadad
Date    : 2.7.19
subject : Binary search tree
*******************************************************************/
#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc*/
#include <assert.h> /* assert */

#include "../include/bst.h" /* typdef struct bst*/ 

#define UNUSED(x) (void)(x)

enum side{LEFT, RIGHT};
enum child{LEFT_C, RIGHT_C, TOW_C, NO_C};

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


static bst_it_t CreatNode(void *data, bst_it_t parent, bst_it_t children_left, 
                          bst_it_t children_right)
{
	bst_it_t node = (bst_it_t)malloc(sizeof(struct bst_node));
		
	if(NULL == node)
	{
		return NULL;
	}
	
	node->data = data;
	node->parent = parent;
	node->children[LEFT] = children_left;
	node->children[RIGHT] = children_right;
	
	return node;
}

static int WhereAreTheKids(bst_it_t node)
{	
	if(NULL != node->children[LEFT])
	{
		if(NULL != node->children[RIGHT])
		{
			return TOW_C;
		}	
		
		return LEFT_C;
	}
	
	if(NULL != node->children[RIGHT])
	{
		return RIGHT_C;
	}
	
	return NO_C;		
}

static int WhoIsYourDaddy(bst_it_t father,bst_it_t son)
{	
	if(son == father->children[RIGHT])
	{
		return RIGHT;
	}	

	return LEFT;		
}

static bst_it_t InTraversal(bst_it_t node, int side)
{
	bst_it_t parent_it = NULL;
	bst_it_t current = node;
	int other_side = LEFT;
	
	if(side == LEFT)
	{
		other_side = RIGHT;	
	} 
		
	if(NULL != current->children[side])
	{
		current = current->children[side];
		
		while(NULL != current->children[other_side])	
		{
			current = current->children[other_side];
		}
		
		return current;
	}
		
	parent_it = current->parent;
		
	while(current != parent_it->children[other_side])	
	{
		current = current->parent;
		parent_it = parent_it->parent;
		
		if(parent_it == NULL)
		{
			break;
		}
	}
		
	return parent_it;	
}

bst_t *BSTCreate(cmp_f compare, const void *params)
{
	bst_t *new_bst = (bst_t *)malloc(sizeof(bst_t));
	
	assert(NULL != compare);
	
	if(NULL == new_bst)
	{
		return NULL;
	}
	
	new_bst->dummy.data = (void *)0xDEADBEEF;
	new_bst->dummy.parent = NULL; 
	new_bst->dummy.children[LEFT] = NULL;
	new_bst->dummy.children[RIGHT] = NULL;
	
	new_bst->compare = compare;
	new_bst->params = (void *)params;
	
	return new_bst;
}

void BSTDestroy(bst_t *bst)
{
	bst_it_t current = (bst_it_t)bst->dummy.children[LEFT];
	bst_it_t current_parent = NULL;
	
	assert(NULL != bst);
	
	while(current_parent != (&bst->dummy))
	{
		if(NULL != current->children[LEFT])
		{
			current = current->children[LEFT];
		}
		
		else if(NULL != current->children[RIGHT])
		{
			current = current->children[RIGHT];
		}
			
		else
		{			
	    	current_parent = current->parent;
	    	free(current);
	    	
	    	if(current == current_parent->children[LEFT])
			{
				current_parent->children[LEFT] = NULL;
			}
			else if(current == current_parent->children[RIGHT])
			{
				current_parent->children[RIGHT] = NULL;
			}
			
			current = current_parent;
		}
	}
	
	free(bst);
}


bst_it_t BSTInsert(bst_t *bst, void *data)
{
	bst_it_t current = (bst_it_t)bst->dummy.children[LEFT];
	bst_it_t new_parent = (bst_it_t)bst;
	bst_it_t new_node = NULL;
	int side = LEFT;
	int cmp_val = 0;
	
	assert(NULL != bst);
	
	new_node = CreatNode(data, NULL, NULL, NULL);
	if(NULL == new_node)
	{
		return NULL;
	}
	
	if(BSTIsEmpty(bst))
	{
		bst->dummy.children[LEFT] = new_node;
		new_node->parent = &bst->dummy;	
		
		return new_node;
	}
	
	while(NULL != current)
	{
		cmp_val = bst->compare(BSTGetData(current), data, bst->params);
		
		if(cmp_val == 0)
		{
			return &bst->dummy;
		}
		
		if(cmp_val > 0)
		{
			side = LEFT;
		}
		else
		{
			side = RIGHT;
		}
				
		new_parent = current;
		current = current->children[side];
	}
	
	new_parent->children[side] = new_node;
	new_node->parent = new_parent;
	
	return new_node;
}
  
void BSTRemove(bst_it_t node)
{
	int kids = WhereAreTheKids(node);
	int side;
	bst_it_t parent_it = node->parent;
	bst_it_t successor = NULL;
	
	assert(NULL != node);
	
	if(kids == NO_C)
	{
		side = WhoIsYourDaddy(parent_it, node);
		parent_it->children[side] = NULL;
		free(node);
	}
	
	if(kids == RIGHT_C || kids == LEFT_C)
	{
			node->data = node->children[kids]->data;
			free(node->children[kids]);
			node->children[kids] = NULL;
		
		/*side = WhoIsYourDaddy(parent_it, node);
		parent_it->children[side] = node->children[kids];
		node->children[kids]->parent = parent_it;
		free(node);	*/
	}
	
	if(kids == TOW_C)
	{
		successor = BSTNext(node);
		node->data = successor->data; 	
		BSTRemove(successor);
	}
}


bst_it_t BSTFind(const bst_t *bst, const void *data)
{
	bst_it_t current = (bst_it_t)bst->dummy.children[LEFT];
	int side = LEFT;
	int cmp_val = 0;
	
	assert(NULL != bst);
	
	while(NULL != current)
	{
		cmp_val = bst->compare(BSTGetData(current), data, bst->params);
		
		if(cmp_val == 0)
		{
			return current;
		}
		
		if(cmp_val > 0)
		{
			side = LEFT;
		}
		else
		{
			side = RIGHT;
		}
				
		current = current->children[side];
	}
	
	return BSTEnd(bst);
}

int BSTForEach(bst_it_t from, bst_it_t to, act_f action, const void *args)
{
	bst_it_t current = from;
	
	assert(NULL != from && NULL != to && NULL != action);
	
	for(; current != to; current = BSTNext(current))
	{
		if(action(current->data, args) == 1)
		{
			return 1;
		}
	}
	
	return 0;
}

bst_it_t BSTPrev(bst_it_t node)
{
	assert(NULL != node);
	
	return InTraversal(node, LEFT);
}

bst_it_t BSTNext(bst_it_t node)
{
	assert(NULL != node);
	
	return InTraversal(node, RIGHT);
}


void *BSTGetData(bst_it_t node)
{
	assert(NULL != node);
	
	return node->data;
}

size_t BSTCount(const bst_t *bst)
{
	size_t count = 0;
	bst_it_t current =  NULL;
	
	assert(NULL != bst);
	
	if(BSTIsEmpty(bst))
	{
		return 0;
	}
	
	current = BSTBegin(bst);
	
	while(current != BSTEnd(bst))
	{
		++count;
		current = BSTNext(current);
	}
	
	return count;
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (NULL == bst->dummy.children[LEFT]);
}

bst_it_t BSTBegin(const bst_t *bst)
{
	bst_it_t current = NULL;
	
	assert(NULL != bst);
	
	current = (bst_it_t)bst;/*.children[LEFT];*/
	
	while(NULL != current->children[LEFT])
	{
		current = current->children[LEFT];
	}
	
	return current;
}

bst_it_t BSTEnd(const bst_t *bst)
{
	assert(NULL != bst);
	
	return(bst_it_t)bst;
}

