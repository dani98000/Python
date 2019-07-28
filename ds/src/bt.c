#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include "bt.h"
#include "dhcp.h"


enum side{LEFT,RIGHT};

typedef struct bt_node
{
	size_t is_full;
	struct bt_node *children[2];
} bt_node_t;

struct bt
{
	size_t num_of_bits;
	bt_node_t *root;
};

static bt_node_t *CreateNode();
static void RecurDestroy(bt_node_t *node);
static enum status RecInsert(bt_node_t *node, int floor, int num_of_bits, uint32_t data, uint32_t *ins_data);
static int RecCount(bt_node_t *node, int floor, int num_of_bits);
static int ChildrenTest(bt_node_t *node);
static void UpdateIsFull(bt_node_t *node);
static void UpdateIsFull2(bt_node_t *node);
static int RecRemove(bt_node_t *node, int floor, int num_of_bits, uint32_t data);


bt_t *BTCreate(size_t num_of_bits)
{
	bt_t *bt = NULL;

	assert(num_of_bits > 0);

	bt = (bt_t *)malloc(sizeof(*bt));
	if(NULL == bt)
	{
		return NULL;
	}

	bt->num_of_bits = num_of_bits;

	bt->root = CreateNode();
	if(NULL == bt->root) 
	{
		free(bt);
		bt = NULL;

		return NULL;
	}

	return bt;
}	

void BTDestroy(bt_t *bt)
{
	assert(bt);

	RecurDestroy(bt->root);
	free(bt);
	bt = NULL;
}

enum status BTInsert(bt_t *bt, uint32_t data, uint32_t *ins_data)
{
	assert(bt);

	enum status status= RecInsert(bt->root, 0, bt->num_of_bits, data, ins_data);
	if(*ins_data != data)
	{
		return ADDR_TAKEN;
	}
	else if(bt->root->is_full == 1)
	{
		return NO_FREE_ADDR;
	}

	return status;
}

int BTRemove(bt_t *bt, uint32_t key)
{
	assert(bt);

	return RecRemove(bt->root, 0, bt->num_of_bits, key);
}

size_t BTCount(const bt_t *bt)
{
	return RecCount(bt->root, 0, bt->num_of_bits) - 2; /* -2 Because of broadcast address and network address */
}

size_t BTCountFree(const bt_t *bt)
{
	return (pow(2, bt->num_of_bits) - BTCount(bt) - 2) ; /* -2 Because of broadcast address and network address */
}

static int RecCount(bt_node_t *node, int floor, int num_of_bits)
{
	if(NULL == node)
	{
		return 0;
	}

	if(floor == num_of_bits)
	{
		return node->is_full;
	} 

	return(RecCount(node->children[LEFT], floor + 1, num_of_bits) + RecCount(node->children[RIGHT], floor + 1, num_of_bits));
}

static int RecRemove(bt_node_t *node, int floor, int num_of_bits, uint32_t key)
{
	int bit = 0;
	int result = 0;
	int shift = 0;
	bt_node_t *child = NULL;


	if(floor == num_of_bits)
	{
		return 0;
	}

	shift = num_of_bits - floor - 1;
	bit = ((0x1 << shift) & key) >> shift;

	child = node->children[bit];
	if(!child)
	{
		return 1; /* There is not matching IP Address */
	}

	result = RecRemove(child,floor + 1, num_of_bits, key);

	UpdateIsFull2(child);
	UpdateIsFull2(node);

	return result;
}


static enum status RecInsert(bt_node_t *node, int floor, int num_of_bits, uint32_t data, uint32_t *ins_data)
{
	int bit = 0, shift = 0;
	bt_node_t *child = NULL;
	int other_side = 0;
	int result = 0;

	if(floor == num_of_bits)
	{
		return OK;
	}

	shift = num_of_bits - floor - 1;
	bit = ((0x1 << shift) & data) >> shift;
	child = node->children[bit];
	other_side = (bit == LEFT) ? RIGHT : LEFT;

	if (NULL == child)
	{
		child = CreateNode();
		if(NULL == child)
		{
			return E_ALLOC;  /* malloc fail */
		}

		node->children[bit] = child;
	}

	if(child->is_full == 1)
	{
		return RecInsert(node, floor, num_of_bits, (data ^ (0x1 << shift)), ins_data);
	}

	*ins_data |= (bit << shift);

	result = RecInsert(child,floor + 1, num_of_bits, data, ins_data);

	UpdateIsFull(child);
	UpdateIsFull(node);

	return result;
}

static void UpdateIsFull(bt_node_t *node) 
{

	if (ChildrenTest(node) == 2)
	{ 
		if (node->children[LEFT]->is_full == 1 && node->children[RIGHT]->is_full == 1)
		{
			node->is_full = 1;
		}
		else
		{
			node->is_full = 0;
		}
	}
	else if (ChildrenTest(node) == 1 || ChildrenTest(node) == 0)
	{
		node->is_full = 0;
	}
	else
	{
		node->is_full = 1;
	}
}

static void UpdateIsFull2(bt_node_t *node)
{

	if (ChildrenTest(node) == 2)
	{ 
		if (node->children[LEFT]->is_full == 0 || node->children[RIGHT]->is_full == 0)
		{
			node->is_full = 0;
		}
	}
	else if (ChildrenTest(node) == 1 || ChildrenTest(node) == 0)
	{
			node->is_full = 0;
	}
	else
	{
		node->is_full = 0;
	}
}

static bt_node_t *CreateNode()
{
	bt_node_t *node = (bt_node_t *)malloc(sizeof(*node));
	if(NULL == node)
	{
		return NULL;
	}
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;	 

	node->is_full = 0;

	return node;
}

static void RecurDestroy(bt_node_t *node)
{
	if(NULL == node)
	{
		return;
	}

	RecurDestroy(node->children[LEFT]);
	RecurDestroy(node->children[RIGHT]);
	free(node);
	node = NULL;
}

static int ChildrenTest(bt_node_t *node)
{
	if (node->children[LEFT] && node->children[RIGHT])
	{
		return 2;
	}
	if (!node->children[LEFT] && node->children[RIGHT])
	{
		return 1;
	}
	if (node->children[LEFT] && !node->children[RIGHT])
	{
		return 0;
	}

	return -1;
}
