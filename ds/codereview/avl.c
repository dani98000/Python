/****************************/
/* Binary Search Tree		*/
/* Author Eran Segal		*/
/* Reviewer - Danil Maizel	*/
/* Date - 14/07/2019		*/
/****************************/

#include <stdio.h>	/* size_t */
#include <sys/types.h> /* ssize_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/avl.h"	/* avl header file */

enum side{LEFT, RIGHT};

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

/* static functions */
static avl_node_t *CreateNode(void *data);
static avl_node_t *Balance(avl_node_t *node);
static ssize_t GetBalanceFactor(avl_node_t *node);
static size_t UpdateHeight(avl_node_t *node);
static avl_node_t *Rotate(avl_node_t *root, int side);
static int cmp_translate(int compare_result);
static int RecurInsert(avl_node_t *node, void *data, avl_cmp_f compare, const void *params);
static void *RecurFind(avl_node_t *node, const void *key, avl_cmp_f compare, const void *params);
static void DeleteNode(avl_node_t *node);
static void RecurDestroy(avl_node_t *node);
static int RecurForEach(avl_node_t *node, avl_act_f Act, const void *args);
static avl_node_t *RecurRemove(avl_node_t *node, const void *key, avl_cmp_f compare, const void *params);
static int CountChildren(avl_node_t *node);
static avl_node_t *KidnapLeftiestChild(avl_node_t *node);
static size_t RecurGetSize(avl_node_t *node);
static void RecurAVLPrint(avl_node_t *node);


static avl_node_t *CreateNode(void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if(new_node)
	{
		new_node->data = data;
		new_node->children[LEFT] = 0;
		new_node->children[RIGHT] = 0;
		new_node->height = 0;
	}
	
	return new_node;
}

static avl_node_t *Balance(avl_node_t *node)
{
	ssize_t balance_factor1 = GetBalanceFactor(node);
	ssize_t balance_factor2 = 0;
	int unbalanced1 = 0;
	int unbalanced2 = 0;
	
	if(-2 ==  balance_factor1 || 2 == balance_factor1)
	{
		unbalanced1 = -2 == balance_factor1;
		balance_factor2 = GetBalanceFactor(node->children[unbalanced1]);
		unbalanced2 = -1 == balance_factor2;
		
		if(unbalanced1 != unbalanced2) /* LR / RL */
		{
			node->children[unbalanced1] = Rotate(node->children[unbalanced1], unbalanced2);
		}
		
		node = Rotate(node, unbalanced1);
	}
	
	return node;
}

static size_t UpdateHeight(avl_node_t *node)
{
	int side = 0 > GetBalanceFactor(node);
	size_t res = 0;
	
	if(node->children[side])
	{
		res = node->children[side]->height + 1;
	}
	
	return res;
}

static ssize_t GetBalanceFactor(avl_node_t *node)
{
	ssize_t left_h = -1;
	ssize_t right_h = -1;
	
	if(node->children[LEFT])
	{
		node->children[LEFT]->height = UpdateHeight(node->children[LEFT]);
		left_h = node->children[LEFT]->height;
	}
	
	if(node->children[RIGHT])
	{
		right_h = node->children[RIGHT]->height;
		node->children[RIGHT]->height = UpdateHeight(node->children[RIGHT]);
	}
	
	return left_h - right_h;
}

static avl_node_t *Rotate(avl_node_t *root, int side) /* insert should call this function to it's relevant child and the finc will check if it needs to change anything(caller_node->children[side] = Rotate(caller_node->children[side], side)) */
{
	int other_side = 0 == side;
	avl_node_t *pivot = root->children[side];
	
	root->children[side] = pivot->children[other_side];
	pivot->children[other_side] = root;
	
	pivot->height = UpdateHeight(pivot);
	
	return pivot;
}

static int cmp_translate(int compare_result)
{
	int res = 0;
	
	if(0 == compare_result)
	{
		res = -1;
	}
	else
	{
		res = 0 > compare_result; /* if true returns RIGHT */
	}
	
	return res;
}

static int RecurInsert(avl_node_t *node, void *data, avl_cmp_f compare, const void *params)
{
	int side = cmp_translate(compare(node->data, data, params));
	int res = 0;
	
	if(0 > side)
	{
		res = 1;/* 1 means duplicate_error */
	}
	else
	{
		if(node->children[side])
		{
			res = RecurInsert(node->children[side], data, compare, params);
			node->height = UpdateHeight(node);
			node->children[side] = Balance(node->children[side]);
		}
		else
		{
			node->children[side] = CreateNode(data);
			res = NULL == node->children[side];
		}
	}
	node->height = UpdateHeight(node);
	
	return res;
}

static void *RecurFind(avl_node_t *node, const void *key, avl_cmp_f compare, const void *params)
{
	int side = 0;
	void *res = NULL;
	if(node)
	{
		res = node->data;
		
		side = cmp_translate(compare(node->data, key, params));
		
		if(-1 != side)
		{
			res = RecurFind(node->children[side], key, compare, params);
		}
	}
	
	return res;
}

static void DeleteNode(avl_node_t *node)
{
	node->data = NULL;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	node->height = 0;
	
	free(node);
}

static void RecurDestroy(avl_node_t *node)
{
	if(node)
	{
		RecurDestroy(node->children[LEFT]);
		RecurDestroy(node->children[RIGHT]);
		DeleteNode(node);
	}
}

static int RecurForEach(avl_node_t *node, avl_act_f Act, const void *args)
{
	int res = 0;
	
	if(node)
	{
		if(0 == RecurForEach(node->children[LEFT], Act, args))
		{
			if(0 == Act(node->data, args))
			{
				res = RecurForEach(node->children[RIGHT], Act, args);
			}
		}
	}
	
	return res;
}

static avl_node_t *RecurRemove(avl_node_t *node, const void *key, avl_cmp_f compare, const void *params)
{
	int side = cmp_translate(compare(node->data, key, params));
	avl_node_t *res = node;
	int children_num = CountChildren(node);;
	
	if(side == -1) /* node->data == key */
	{
		if(2 == children_num)
		{
			res = KidnapLeftiestChild(node->children[RIGHT]);
			res->children[LEFT] = node->children[LEFT];
			if(res != node->children[RIGHT])
			{
				res->children[RIGHT] = node->children[RIGHT];
			}
		}
		else if(0 <= children_num)
		{
			res = node->children[children_num];
		}
		else
		{
			res = NULL;
		}
		DeleteNode(node);
	}
	else
	{
		node->children[side] = RecurRemove(node->children[side], key, compare, params);
		node->height = UpdateHeight(node);
		res = Balance(node);
	}
	
	return res;
}

static int CountChildren(avl_node_t *node)
{
	int res = -1;
	if(node->height)
	{
		if(node->children[LEFT] && node->children[RIGHT])
		{
			res = 2;
		}
		else if(node->children[LEFT])
		{
			res = 0;
		}
		else
		{
			res = 1;
		}
	}
	return res;
}

static avl_node_t *KidnapLeftiestChild(avl_node_t *node)
{
	avl_node_t *res = node;
	
	if(node->children[LEFT])
	{
		if(node->children[LEFT]->children[LEFT])
		{
			res = KidnapLeftiestChild(node->children[LEFT]);
		}
		else
		{
			res = node->children[LEFT];
			node->children[LEFT] = node->children[LEFT]->children[RIGHT];
		}
	node->height = UpdateHeight(node);
	}
	
	return res;
}

static size_t RecurGetSize(avl_node_t *node)
{
	size_t cnt = 0;
	if(node)
	{
		++cnt;
		cnt += RecurGetSize(node->children[LEFT]);
		cnt += RecurGetSize(node->children[RIGHT]);
	}
	
	return cnt;
}

/* Formal functions */
avl_t *AVLCreate(avl_cmp_f compare, const void *params)
{
	avl_t *new_avl = NULL;
	
	assert(compare);
	
	new_avl = (avl_t *)malloc(sizeof(avl_t));
	if(new_avl)
	{
		new_avl->root = NULL;
		new_avl->compare = compare;
		new_avl->params = params;
	}
	
	return new_avl;
}

void AVLDestroy(avl_t *avl)
{
	assert(avl);
	
	RecurDestroy(avl->root);
	
	avl->compare = NULL;
	avl->params = NULL;
	free(avl);
}

int AVLInsert(avl_t *avl, void *data)
{
	int res = 0;
	
	assert(avl);
	
	if(AVLIsEmpty(avl))
	{
		avl->root = CreateNode(data);
		res = NULL != avl->root;
	}
	else
	{
		res = RecurInsert(avl->root, data, avl->compare, avl->params);
		avl->root = Balance(avl->root);
	}
	
	return res;
}

void AVLRemove(avl_t *avl, const void *key)
{
	assert(avl);
	assert(!AVLIsEmpty(avl));
	
	avl->root = RecurRemove(avl->root, key, avl->compare, avl->params);
}

int AVLForEach(avl_t *avl, avl_act_f Act, const void *args)
{
	assert(avl);
	assert(Act);
	
	return RecurForEach(avl->root, Act, args);
}

void *AVLFind(const avl_t *avl, const void *key)
{
	assert(avl);
	
	return RecurFind(avl->root, key, avl->compare, avl->params);
}

size_t AVLSize(const avl_t *avl)
{
	assert(avl);
	
	return RecurGetSize(avl->root);
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);
	
	return NULL == avl->root;
}

size_t AVLGetHeight(const avl_t *avl)
{
	assert(avl);
	assert(avl->root);
	
	return avl->root->height;
}
