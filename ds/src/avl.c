#include <stdlib.h>
#include <assert.h>

#include "../include/avl.h"

enum children{LEFT, RIGHT};

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

static avl_node_t *CreateNode(void *data);
static avl_node_t *SameSideRotataion(avl_node_t *root ,int side);
static int GetBalanceFactor(avl_node_t *root);
static int GetMaxHeight(avl_node_t *node);
static size_t RecSize(avl_node_t *node);
static int InOrder(avl_node_t *node, avl_act_f act, const void *args);
static int IsRChild(avl_node_t *node);
static int IsLChild(avl_node_t *node);
static int IsLeaf(avl_node_t *node);
static avl_node_t *RecInsert(avl_node_t *node, avl_node_t *parent, int side, void *data, avl_cmp_f compare);
static void NodeToDestroy(avl_node_t *node);
static void *RecFind(avl_node_t *node, const void *key, avl_cmp_f compare);
static void RecFindToRemove(avl_node_t *node, avl_node_t *parent, const void *key, avl_cmp_f compare);
static int ChildrenTest(avl_node_t *node);
void RecRemove(avl_node_t *node, avl_node_t *parent, const void *key, avl_cmp_f compare);
static avl_node_t *GetLeftiestChild(avl_node_t *node);
static int IsMyRChild(avl_node_t *node, avl_node_t *parent);

avl_node_t *GetRoot(avl_t *tree)
{
	printf("daniel");
	return tree->root;
}

void *GetData(avl_node_t *root)
{
	printf("%d", root->height);
	return root->data;
}

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
	if(AVLIsEmpty(avl))
	{
		avl->root = CreateNode(data);
	/*	avl->root->height += 1;*/
		return 0;
	}
	RecInsert((avl_node_t *)avl->root , NULL, 0, data, avl->compare);
	return 1;	
}

static avl_node_t *RecInsert(avl_node_t *node, avl_node_t *parent, int side, void *data, avl_cmp_f compare)
{
	int res = 0;
	avl_node_t *current = NULL;
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
	/*if(ChildrenTest(node) == 0)
	{
		node->height = node->children[LEFT]->height + 1;
	}
	else if (ChildrenTest(node) == 1)
	{
		node->height = node->children[RIGHT]->height + 1;
	}*/	
	res = compare(node->data, data, NULL);
	
	if(res > 0)
	{
		node->height = node->children[LEFT]->height;
		node = RecInsert(node->children[LEFT], node, LEFT, data, compare);
	}
	if(res < 0)
	{
		if(IsRChild(node))
		{
			node->height = node->children[RIGHT]->height;
		}
		node = RecInsert(node->children[RIGHT], node, RIGHT, data, compare);
	}
	
	
	/*node->height = GetMaxHeight(node) + 1;
	balance_factor = GetBalanceFactor(node);
	
	if(balance_factor > 1 && data > node->children[LEFT]->data) /* LR *
	{
		node->children[LEFT] = SameSideRotataion(node->children[LEFT], LEFT);
		return SameSideRotataion(node, RIGHT);
	}
	if(balance_factor > 1 && data < node->children[LEFT]->data) /* LL *
	{
		return SameSideRotataion(node, RIGHT);
	}
	if(balance_factor < -1 && data < node->children[RIGHT]->data) /* RL *
	{
		node->children[RIGHT] = SameSideRotataion(node->children[RIGHT], RIGHT);
		return SameSideRotataion(node, LEFT);
	}
	if(balance_factor < -1 && data > node->children[RIGHT]->data)/* RR *
	{
		return SameSideRotataion(node, LEFT);
	}*/
	
	return 0;
}

int AVLIsEmpty(const avl_t *avl)
{
	return avl->root == NULL;
}

size_t AVLSize(const avl_t *avl)
{
	return RecSize(avl->root);
}

int AVLForEach(avl_t *avl, avl_act_f Act, const void *args)
{
	assert(NULL != avl);
	
	return InOrder(avl->root, Act, args);
}

size_t AVLGetHeight(const avl_t *avl)
{
	assert(NULL != avl);
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
	return RecFind(avl->root, key, avl->compare);
}

void AVLRemove(avl_t *avl, const void *key)
{
	if(!AVLIsEmpty(avl))
	{
		RecFindToRemove(avl->root, NULL, key, avl->compare);
	}
}

void RecRemove(avl_node_t *node, avl_node_t *parent, const void *key, avl_cmp_f compare)
{
	int kids_side = ChildrenTest(node);
	int side = 0;
	avl_node_t *temp = NULL;

	if(node == NULL)
	{
		return;
	}
	if(IsLeaf(node))
	{
		side = IsMyRChild(node, parent) ? RIGHT : LEFT;
		free(node);
		parent->children[side] = NULL;
	}
	
	else if(ChildrenTest(node) == 2)
	{
		if(!IsLChild(node->children[RIGHT]))
		{
			node->data = node->children[RIGHT]->data;
			RecRemove(node->children[RIGHT], node, key, compare);
		}
		else
		{
 			temp = GetLeftiestChild(node->children[RIGHT]);
 			node->data = temp->children[LEFT]->data;
 			free(temp->children[LEFT]);
 			temp->children[LEFT] = NULL;
		}
	}
	
	else
	{
		side = IsMyRChild(node, parent) ? RIGHT : LEFT;
		parent->children[side] = node->children[kids_side];
		free(node);
	}
	
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

static void RecFindToRemove(avl_node_t *node, avl_node_t *parent, const void *key, avl_cmp_f compare)
{
	int side = 0;
	int res = 0;
	
 	if(node)
 	{
 		res = compare(node->data, key, NULL);
 
		if(0 == res)
		{
			RecRemove(node, parent, key, compare);
			return;
		}
		
		side = res > 0 ? LEFT : RIGHT; 
		RecFindToRemove(node->children[side], node, key, compare);
	}
}

static void *RecFind(avl_node_t *node, const void *key, avl_cmp_f compare)
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

static avl_node_t *GetLeftiestChild(avl_node_t *node)
{	
	avl_node_t *temp = node;
	
	if(node->children[LEFT])
	{
		if(node->children[LEFT]->children[LEFT])
		{
			 temp = GetLeftiestChild(node->children[LEFT]);
		}
		else
		{
			temp = node;
		}
	}

	return temp;
}

static int GetMaxHeight(avl_node_t *node)
{
	size_t r_child_height = 0;
	size_t l_child_height = 0;
	
	if(node->children[RIGHT])
	{
		r_child_height = node->children[RIGHT]->height;
	}
	if(node->children[LEFT])
	{
		l_child_height = node->children[LEFT]->height;
	}
	
	return r_child_height > l_child_height ? r_child_height : l_child_height;
}

static avl_node_t *SameSideRotataion(avl_node_t *root ,int side)
{
	int other_side = side == LEFT;
	avl_node_t *pivot = root->children[side];
	avl_node_t *pivot_child = pivot->children[other_side];
	
	pivot->children[other_side] = root;
	root->children[side] = pivot_child;
	
	return pivot;
}

/*static avl_node_t * DifferentSideRotation(avl_node_t *root, int side)
{
	int other_side = side == LEFT;
	avi_node_t *pivot_child = pivot->children[side];
	avi_node_t *pivot = root->children[other_side];
	
	pivot = root;
	
	

}*/

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

/*static int CompareGetSide()*/

static int GetBalanceFactor(avl_node_t *root)
{
	int height_left = -1;
	int height_right = -1;
	
	if(root->children[RIGHT] != NULL)
	{
		height_right = root->children[RIGHT]->height;
	}
	if(root->children[LEFT] != NULL)
	{
		height_right = root->children[LEFT]->height;
	}
	
	return height_left - height_right;
}

static int IsRChild(avl_node_t *node)
{
	return node->children[RIGHT] != NULL;
}

static int IsLChild(avl_node_t *node)
{
	return node->children[LEFT] != NULL;
}

static int IsLeaf(avl_node_t *node)
{
	return node->children[LEFT] == NULL && node->children[RIGHT] == NULL;
}

static int IsMyRChild(avl_node_t *node, avl_node_t *parent)
{
	return parent->children[RIGHT] == node;
}
