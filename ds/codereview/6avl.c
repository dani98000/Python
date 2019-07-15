/*************************************************************************************/
/* AVL Tree                                                                          */
/* Author- Inbar Namdar                                                              */
/* Reviewer - Eran Segal                                                             */
/* Date - 04/07/2019                                                                 */
/*************************************************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <sys/types.h> /* ssize_t */
#include "../include/avl.h" /* AVL header file */

struct avl_node
{
	void *data;
	struct avl_node *children[2];
	size_t height;
};

 struct avl
{
	avl_node_t *root;
	avl_cmp_f compare;
	const void *params;
};

enum kids{LEFT, RIGHT,TWO,NONE};
static ssize_t GetNodeHeight(avl_node_t *node);
static ssize_t GetMaxHeight(avl_node_t *node);
static avl_node_t *SameSideRotataion(avl_node_t *root ,int side);
static avl_node_t *DBalance(avl_node_t *node);
static avl_node_t *CreateAVLNode(void *data);
static int HowManyChildren(avl_node_t *node);
static void DisconnectParent(avl_node_t *node, avl_node_t *parent);
static int GetBalanceFactor(avl_node_t *node);
static avl_node_t *Balance(avl_node_t *node, int balance_factor);
static avl_node_t *LeftLeftRotation(avl_node_t *node);
static avl_node_t *RightRightRotation(avl_node_t *node);
static avl_node_t *RightLeftRotation(avl_node_t *node);
static avl_node_t *LeftRightRotation(avl_node_t *node);
static void RecursiveDestroy(avl_node_t *node);
static int RecursiveInsertNode(avl_node_t *node, avl_node_t *parent, 
		int side, void *data, avl_t *avl); 
static avl_node_t *FindLefmost(avl_node_t *node);
static void NodeRemove(avl_node_t *node, avl_node_t *parent, avl_t *avl); 
static void RecursiveFindNodeToRemove(avl_node_t *node, avl_node_t *parent, 
			const void *key, avl_t *avl);
static int RecursiveForEach(avl_node_t *node, avl_act_f Act, const void *args);
static void *RecursiveFind(avl_node_t *node, const void *key, avl_t *avl);
static size_t RecursiveSize(avl_node_t *node);
					
			
static avl_node_t *CreateAVLNode(void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->height = 0;
	
	return new_node;
}

static int HowManyChildren(avl_node_t *node)
{
	if (NULL != node->children[RIGHT] && NULL != node->children[LEFT])
	{
		return TWO;
	}
	else if (NULL != node->children[RIGHT] && NULL == node->children[LEFT])		
	{
		return RIGHT;
	}
	else if (NULL == node->children[RIGHT] && NULL != node->children[LEFT])
	{
		return LEFT;
	}
	return NONE;
}

static void DisconnectParent(avl_node_t *node, avl_node_t *parent)
{
	if (node == parent->children[LEFT])
	{
		parent->children[LEFT] = NULL;
	}
	else 
	{
		parent->children[RIGHT] = NULL;
	}
}

static int GetBalanceFactor(avl_node_t *node)
{
	ssize_t r_child_height = GetNodeHeight(node->children[RIGHT]);
	ssize_t l_child_height = GetNodeHeight(node->children[LEFT]);
		
	return l_child_height - r_child_height;
}

static void Updateheight(avl_node_t *root)
{
	long left = -1, right = -1;
	
	if(NULL != root->children[RIGHT] && root)
	{
		if(root)
		{
			Updateheight(root->children[RIGHT]);
		}		
		right =  root->children[RIGHT]->height;
	}
	
	if(NULL != root->children[LEFT] && root)
	{
		if(root)
		{
			Updateheight(root->children[LEFT]);
		
		left =  root->children[LEFT]->height;
	}
	
	root->height = left > right ? left + 1 : right + 1;
}

static avl_node_t *Balance(avl_node_t *node, int balance_factor)
{
	
	if(balance_factor > 1)
	{
		if(GetBalanceFactor(node->children[LEFT]) >= 0)
		{
			return SameSideRotataion(node, RIGHT);
		}
		
		node->children[LEFT] = SameSideRotataion(node->children[LEFT], LEFT);
		
		return SameSideRotataion(node, RIGHT);
	}
	
	if(balance_factor < -1)
	{		
		if(GetBalanceFactor(node->children[RIGHT]) <= 0)
		{
			return SameSideRotataion(node, LEFT);
		}
	
		node->children[RIGHT] = SameSideRotataion(node->children[RIGHT], RIGHT);
		
		return SameSideRotataion(node, LEFT);
	}
	
	return node;
}

static avl_node_t *LeftLeftRotation(avl_node_t *node)
{
	avl_node_t *root = node;
	avl_node_t *pivot = node->children[RIGHT];
	printf("LEFT ROTATION\n");
	
	root->children[RIGHT] = pivot->children[LEFT];
	pivot->children[LEFT] = root;
	
	
	return pivot;
}

static avl_node_t *RightRightRotation(avl_node_t *node)
{
	avl_node_t *root = node;
	avl_node_t *pivot = node->children[LEFT];
	printf("RIGHT ROTATION\n");
	
	root->children[LEFT] = pivot->children[RIGHT];
	pivot->children[RIGHT] = root;
	
	return pivot;
}

static avl_node_t *LeftRightRotation(avl_node_t *node)
{
	avl_node_t *root = node->children[LEFT];
	avl_node_t *pivot = node->children[LEFT]->children[RIGHT];
	printf("LEFT-RIGHT ROTATION\n");
	
	node->children[LEFT] = pivot;
	root->children[RIGHT] = pivot->children[LEFT];
	pivot->children[LEFT] = root;
	RightRightRotation(node);
	
	return pivot;
}

static avl_node_t *RightLeftRotation(avl_node_t *node)
{
	avl_node_t *root = node->children[RIGHT];
	avl_node_t *pivot = node->children[RIGHT]->children[LEFT];
	printf("RIGHT-LEFT ROTATION\n");
	
	node->children[RIGHT] = pivot;
	root->children[LEFT] = pivot->children[RIGHT];
	pivot->children[RIGHT] = root;
	LeftLeftRotation(node);
	
	return pivot;
}

avl_t *AVLCreate(avl_cmp_f Compare, const void *params)
{
	avl_t *new_avl = NULL;

	assert(Compare);
	
	new_avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == new_avl)
	{
		return NULL;
	}
		
	new_avl->root = NULL;
	new_avl->compare = Compare;
	new_avl->params = (void *)params;
	
	return new_avl;	
}

static void RecursiveDestroy(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	RecursiveDestroy(node->children[LEFT]);
	RecursiveDestroy(node->children[RIGHT]);

	free(node);
}

void AVLDestroy(avl_t *avl)
{
	assert(avl);
	
	RecursiveDestroy(avl->root);
	
	free(avl);
}

static int RecursiveInsertNode(avl_node_t *node, avl_node_t *parent, 
		int side, void *data, avl_t *avl) 
{
	int result = 0;
	int balance_factor = 0;
	
	if (node == NULL)
	{
		node = CreateAVLNode(data);
		if (NULL == node)
		{
			return 1;
		}
			
		parent->children[side] = node;
			
		return 0;
	}
	
	result = avl->compare(node->data, data, avl->params);
	
	if (0 == result)
	{
		return 1;	
	}
	if (0 > result) /* go right */
	{
		RecursiveInsertNode(node->children[RIGHT], node, RIGHT, data, avl);
		balance_factor = GetBalanceFactor(node);
		
		if (-1 > balance_factor || (1 < balance_factor))
		{
			if(NULL == parent)
			{
				avl->root = DBalance(node);
			}
			else
			{
				parent->children[RIGHT] = DBalance(node);
			}
		}
	}
	else /* go left */
	{
		RecursiveInsertNode(node->children[LEFT], node, LEFT, data, avl);
		balance_factor = GetBalanceFactor(node);
		if (-1 > balance_factor || (1 < balance_factor))
		{
			if(NULL == parent)
			{
				avl->root = DBalance(node);
			}
			else if(node)
			{
				parent->children[LEFT] = DBalance(node);
			}
		} 
	}
	
	if(node)
	Updateheight(node);
}

int AVLInsert(avl_t *avl, void *data)
{
	assert(avl);
	
	if (NULL == avl->root)
	{
		avl->root = CreateAVLNode(data);
		if (NULL == avl->root)
		{
			return 1;
		}
		
		return 0;
	}
	
	return RecursiveInsertNode(avl->root, NULL, NONE, data, avl);
}

static avl_node_t *FindLefmost(avl_node_t *node)
{
	if (NULL == node->children[LEFT])
	{
		return node;
	}
	
	FindLefmost(node->children[LEFT]);
}

static void NodeRemove(avl_node_t *node, avl_node_t *parent, avl_t *avl)
{
	avl_node_t *remove = NULL;
	int children = 0;
	int balance_factor = 0;
		
	children = HowManyChildren(node);
	
	if (NONE == children)
	{
		DisconnectParent(node, parent);
		
		free(node);
		
	}
	else if ((LEFT == children) || (RIGHT == children)) 
	{
		remove = node->children[children];
		node->data = remove->data;
		node->children[children] = remove->children[children];
		DisconnectParent(remove, node);
		
		free(remove); 	
	}
	else
	{
		if (NULL != node->children[RIGHT]->children[LEFT])
		{
			remove = FindLefmost(node->children[RIGHT]); 
		}
		else
		{
			remove = node->children[RIGHT]; 
		}
		node->data = remove->data;
		RecursiveFindNodeToRemove(node->children[RIGHT], node, remove->data, avl);
		
		balance_factor = GetBalanceFactor(node);
		
		if (-1 > balance_factor || (1 < balance_factor))
		{
			if (NULL == parent)
			{
				avl->root = Balance(node, balance_factor);
			}
			else
			{
				parent->children[RIGHT]= DBalance(node);
			}
		} 	
	}
		
}

static void RecursiveFindNodeToRemove(avl_node_t *node, avl_node_t *parent, 
			const void *key, avl_t *avl)
{
	int result = 0;
	int balance_factor = 0;
	
	if (NULL == node)
	{
		return;
	}
	
	result = avl->compare(node->data, key, avl->params);
	if (0 == result)
	{
		NodeRemove(node, parent, avl);	
	}
	if (0 > result)
	{
		RecursiveFindNodeToRemove(node->children[RIGHT], node, key, avl);
		balance_factor = GetBalanceFactor(node);
		
		if (-1 > balance_factor || (1 < balance_factor))
		{
			if (NULL == parent)
			{
				avl->root = Balance(node, balance_factor);
			}
			else
			{
				parent->children[RIGHT] = Balance(node, balance_factor);
			}
		}
	}
	else
	{
		RecursiveFindNodeToRemove(node->children[LEFT], node, key, avl);
		balance_factor = GetBalanceFactor(node);
		
		if (-1 > balance_factor || (1 < balance_factor))
		{
			if (NULL == parent)
			{
				avl->root = Balance(node, balance_factor);
			}
			else
			{
				parent->children[LEFT] = Balance(node, balance_factor);
			}
		}
	}
		node->height = GetMaxHeight(node) + 1;
}


void AVLRemove(avl_t *avl, const void *key)
{
	assert(avl);
	assert(key);
	
	RecursiveFindNodeToRemove(avl->root, NULL, key, avl);
}

static int RecursiveForEach(avl_node_t *node, avl_act_f Act, const void *args)
{
	if (node == NULL)
	{
		return 0;
	}

	RecursiveForEach(node->children[LEFT], Act, args);
	
	if (1 == Act(node->data, args))
	{
		return 1;
	}
		
	RecursiveForEach(node->children[RIGHT], Act, args);
	
	return 0;	
}

int AVLForEach(avl_t *avl, avl_act_f Act, const void *args)
{
	assert(avl);
	assert(Act);
	
	return RecursiveForEach(avl->root, Act, args);
}

static void *RecursiveFind(avl_node_t *node, const void *key, avl_t *avl)
{
	int result = 0;
	
	if (node == NULL)
	{
		return NULL;
	}
	
	result = avl->compare(node->data, key, avl->params);
		
	if (0 == result)
	{
		return node->data;
	}
	else if (0 < result)
	{
		RecursiveFind(node->children[LEFT], key, avl);
	}
	else
	{
		RecursiveFind(node->children[RIGHT], key, avl);
	}
}

void *AVLFind(const avl_t *avl, const void *key)
{
	assert(avl);
	assert(key);
	
	return RecursiveFind(avl->root, key, (avl_t *)avl);
}

static size_t RecursiveSize(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return 1 + RecursiveSize(node->children[LEFT]) + RecursiveSize(node->children[RIGHT]);
}

size_t AVLSize(const avl_t *avl)
{
	assert(avl);
	
	return RecursiveSize(avl->root);
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);
	
	return (NULL == avl->root);
}

size_t AVLGetHeight(const avl_t *avl)
{
	assert (avl);
	assert (avl->root);
	
	return avl->root->height;
}

static avl_node_t *DBalance(avl_node_t *node)
{
	int balance_factor = GetBalanceFactor(node);
	
	if(balance_factor > 1)
	{
		if(GetBalanceFactor(node->children[LEFT]) >= 0)
		{
			return SameSideRotataion(node, RIGHT);
		}
		
		node->children[LEFT] = SameSideRotataion(node->children[LEFT], LEFT);
		
		return SameSideRotataion(node, RIGHT);
	}
	
	if(balance_factor < -1)
	{		
		if(GetBalanceFactor(node->children[RIGHT]) <= 0)
		{
			return SameSideRotataion(node, LEFT);
		}
	
		node->children[RIGHT] = SameSideRotataion(node->children[RIGHT], RIGHT);
		
		return SameSideRotataion(node, LEFT);
	}
	
	return node;
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
