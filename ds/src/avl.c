/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 11/07/2019		*
*	 Reviewer: Sandra          	*
*								*
*********************************/
#include <stdlib.h>	/* malloc */
#include <assert.h> /* assert */
#include <sys/types.h> /* ssize_t */
#include <stdio.h> /*debug */

#include "../include/avl.h"/* AVL Header file */

enum children{LEFT, RIGHT};

struct avl_node
{
	void *data;
	struct avl_node *children[2];
	ssize_t height;
};

struct avl
{
	avl_node_t *root;
	avl_cmp_f compare;
	const void *params;
};

static avl_node_t *CreateNode(void *data);
static avl_node_t *SameSideRotataion(avl_node_t *root ,int side);
static int GetBalanceFactor(avl_node_t *root);
static ssize_t GetMaxHeight(avl_node_t *node);
static size_t RecSize(avl_node_t *node);
static int InOrder(avl_node_t *node, avl_act_f act, const void *args);
static int IsLeaf(avl_node_t *node);
static avl_node_t *RecInsert(avl_node_t *node, avl_node_t *parent, int side, void *data, avl_cmp_f compare);
static void NodeToDestroy(avl_node_t *node);
static avl_node_t *RecFind(avl_node_t *node, const void *key, avl_cmp_f compare);
static int ChildrenTest(avl_node_t *node);
static avl_node_t *RecRemove(avl_node_t *node, const void *key, avl_cmp_f compare);
static avl_node_t *GetSuccessor(avl_node_t *node);
static avl_node_t *Balance(avl_node_t *node);
static void PrintTree(avl_node_t *root);/* Utility Function for tests only! */

avl_t *AVLCreate(avl_cmp_f compare, const void *params)
{
	avl_t *avl = (avl_t *)malloc(sizeof(avl_t));
	if(NULL == avl)
	{
		return NULL;
	}
	
	avl->root = NULL;
	avl->compare = compare;
	avl->params = params;
	
	return avl;
}

int AVLInsert(avl_t *avl, void *data)
{
	assert(avl);

	avl->root = RecInsert((avl_node_t *)avl->root , NULL, 0, data, avl->compare);
	
	return 1;	
}

static avl_node_t *RecInsert(avl_node_t *node, avl_node_t *parent, int side, void *data, avl_cmp_f compare)
{
	int res = 0;
	int balance_factor = 0;
	
	if(node == NULL)
	{
		node = CreateNode(data);
		if(parent != NULL)
		{
			parent->children[side] = node;
		}
		
		return node;
	}

	res = compare(node->data, data, NULL);
	
	if(res > 0)
	{
		node->children[LEFT] = RecInsert(node->children[LEFT], node, LEFT, data, compare);
	}
	if(res < 0)
	{
		node->children[RIGHT] = RecInsert(node->children[RIGHT], node, RIGHT, data, compare);
	}
	
	balance_factor = GetBalanceFactor(node);
	
	if(abs(balance_factor) > 1)
	{
		node = Balance(node);
	}
	
	node->height = GetMaxHeight(node) + 1;
	
	return node;
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);

	return avl->root == NULL;
}

size_t AVLSize(const avl_t *avl)
{
	assert(avl);

	return RecSize(avl->root);
}

int AVLForEach(avl_t *avl, avl_act_f Act, const void *args)
{
	assert(avl);
	
	return InOrder(avl->root, Act, args);
}

size_t AVLGetHeight(const avl_t *avl)
{
	assert(avl);
	
	if(avl->root == NULL)
	{
		return 0;
	}
	
	return avl->root->height;
}

void AVLDestroy(avl_t *avl)
{
	if(!AVLIsEmpty(avl))
	{
		NodeToDestroy(avl->root);
	}

	free(avl);
}

void *AVLFind(const avl_t *avl, const void *key)
{
	assert(avl);

	return RecFind(avl->root, key, avl->compare);
}

void AVLRemove(avl_t *avl, const void *key)
{
	assert(avl);

	if(!AVLIsEmpty(avl))
	{
		RecRemove(avl->root, key, avl->compare);
	}
}

static avl_node_t *RecRemove(avl_node_t *node, const void *key, avl_cmp_f compare)
{
	int side = 0;
	avl_node_t *temp = NULL;
	int res = 0;
	
	if(node == NULL)
	{
		return node;
	}
	res = compare(node->data, key, NULL);
	
	if(res > 0)
	{
		node->children[LEFT] = RecRemove(node->children[LEFT], key, compare);
	}
	
	else if(res < 0)
	{
		node->children[RIGHT] = RecRemove(node->children[RIGHT], key, compare);
	}
	
	else
	{
		if(IsLeaf(node))
		{
			free(node);
			
			return NULL;
		}
	
		else if(ChildrenTest(node) == 2)
		{
 			temp = GetSuccessor(node->children[RIGHT]);
 			node->data = temp->data;
			temp->children[RIGHT] = RecRemove(node->children[RIGHT], temp->data, compare);
		}
	
		else if(ChildrenTest(node) == 1 || ChildrenTest(node) == 0)
		{
			side = ChildrenTest(node);
			temp = node->children[side];
			free(node);
			
			return temp;
		}
	}
	
	if(abs(GetBalanceFactor(node))> 1)
	{
		node = Balance(node);
	}
	
	node->height = GetMaxHeight(node) + 1;
	
	return node;
}

static int ChildrenTest(avl_node_t *node)
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

static avl_node_t *Balance(avl_node_t *node)
{
	int balance_factor = GetBalanceFactor(node);
	
	if(balance_factor > 1)
	{
		if(GetBalanceFactor(node->children[LEFT]) > 0)
		{
			return SameSideRotataion(node, RIGHT);
		}
		
		node->children[LEFT] = SameSideRotataion(node->children[LEFT], LEFT);
		
		return SameSideRotataion(node, RIGHT);
	}
	
	if(balance_factor < -1)
	{		
		if(GetBalanceFactor(node->children[RIGHT]) < 0)
		{
			return SameSideRotataion(node, LEFT);
		}
	
		node->children[RIGHT] = SameSideRotataion(node->children[RIGHT], RIGHT);
		
		return SameSideRotataion(node, LEFT);
	}
}

static avl_node_t *RecFind(avl_node_t *node, const void *key, avl_cmp_f compare)
{
	int side = 0;
	int res = compare(node->data, key, NULL);

	if(0 == res)
	{
		return node->data; 
	}
	
	side = res > 0 ? LEFT : RIGHT; 
	RecFind(node->children[side], key, compare);
	
	if(NULL == node)
	{
		return NULL;
	}
}

static void NodeToDestroy(avl_node_t *node)
{
	if(node == NULL)
	{
		return;
	}
	
	NodeToDestroy(node->children[LEFT]);
	NodeToDestroy(node->children[RIGHT]);
	
	free(node);
}

static size_t RecSize(avl_node_t *node)
{	
	if(!node)
	{
		return 0;
	}

	return 1 + (RecSize(node->children[RIGHT]) + RecSize(node->children[LEFT]));
}

static int InOrder(avl_node_t *node, avl_act_f act, const void *args)
{
	int status = 0;	
	
	if(NULL == node)
	{
		return 0;
	}
	
	status = InOrder(node->children[LEFT], act, args);
		
	if(status != 0)
	{
		return status;
	}
	
	status = (act)(node->data, args);
	
	if(status != 0)
	{
		return status;
	}
	
	return InOrder(node->children[RIGHT], act, args);
}

static avl_node_t *GetSuccessor(avl_node_t *node)
{		
	if(NULL == node->children[LEFT])
	{
		return node;
	}

	return GetSuccessor(node->children[LEFT]);
}

static ssize_t GetNodeHeight(avl_node_t *node)
{
	if(NULL == node)
	{
		return -1;
	}
	
	return node->height;
}

static ssize_t GetMaxHeight(avl_node_t *node)
{
	ssize_t r_child_height = GetNodeHeight(node->children[RIGHT]);
	ssize_t l_child_height = GetNodeHeight(node->children[LEFT]);
	
	return r_child_height > l_child_height ? r_child_height : l_child_height;
}

static avl_node_t *SameSideRotataion(avl_node_t *root ,int side)
{
	int other_side = side == LEFT;
	avl_node_t *pivot = root->children[other_side];
	avl_node_t *pivot_child = pivot->children[side];
	
	pivot->children[side] = root;
	root->children[other_side] = pivot_child;
	
	root->height = GetMaxHeight(root) + 1;
	pivot->height = GetMaxHeight(pivot) + 1;
	
	return pivot;
}

static avl_node_t *CreateNode(void *data)
{
	avl_node_t *node = NULL;
	
	assert(NULL != data);
	
	node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if(NULL == node)
	{
		return NULL;
	}
	
	node->data = data;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	node->height = 0;
	
	return node;
}

static int GetBalanceFactor(avl_node_t *root)
{
	ssize_t r_child_height = GetNodeHeight(root->children[RIGHT]);
	ssize_t l_child_height = GetNodeHeight(root->children[LEFT]);
		
	return l_child_height - r_child_height;
}

static int IsLeaf(avl_node_t *node)
{
	return node->children[LEFT] == NULL && node->children[RIGHT] == NULL;
}

static void PrintTree(avl_node_t *root)
{
	if(NULL == root)
	{
		return;
	}
	
	printf("data: %d height: %ld balance: %d ", *(int *)root->data, root->height, 				GetBalanceFactor(root));
	
	if(NULL != root->children[LEFT])
	{
		printf(" left: %d ", *(int *)root->children[LEFT]->data);
	}
	
	if(NULL != root->children[RIGHT])
	{
		printf(" right: %d ", *(int *)root->children[RIGHT]->data);
	}
	
	printf("\n");
	
	PrintTree(root->children[LEFT]);
	PrintTree(root->children[RIGHT]);
}
