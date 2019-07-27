#include <assert.h>
#include <stdlib.h>

#include "bt.h"

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
static int RecInsert(bt_node_t *node, int floor, int num_of_bits, uint32_t data);
static int RecCount(bt_node_t *node, int floor, int num_of_bits);


bt_t *BTCreate(size_t num_of_bits)
{
	bt_t *trie = NULL;

	assert(num_of_bits > 0);

	trie = (bt_t *)malloc(sizeof(*trie));
	if(NULL == trie)
	{
		return NULL;
	}

	trie->num_of_bits = num_of_bits;
	trie->root = CreateNode();
	if(NULL == trie->root) 
	{
		free(trie);
		trie = NULL;

		return NULL;
	}

	return trie;
}	

void BTDestroy(bt_t *bt)
{
	assert(bt);

	RecurDestroy(bt->root);
	free(bt);
	bt = NULL;
}

int BTInsert(bt_t *bt, uint32_t data)
{
	assert(bt);

	return RecInsert(bt->root, 0, bt->num_of_bits, data);
}

static int RecInsert(bt_node_t *node, int floor, int num_of_bits, uint32_t data)
{
	int bit = 0;
	bt_node_t *child = NULL;
	int other_side = 0;
	if(floor == num_of_bits)
	{
		return 0;
	}

	bit = ((0x1 << floor) & data) >> floor;
	child = node->children[bit];

	if (NULL == child)
	{
		child = CreateNode();
		if(NULL == child)
		{
			return 1;  /* malloc fail */
		}

		node->children[bit] = child;
	}
	else if(child->is_full == 1)
	{
		return 2; /* duplicate */
	}

	return RecInsert(child,floor + 1, num_of_bits, data);
	
	child->is_full = 1;

	other_side = bit == LEFT ? RIGHT : LEFT;
	if(node->children[other_side]->is_full == 1)
	{
		node->is_full = 1;
	}
}

size_t BTCount(const bt_t *bt)
{
	return RecCount(bt->root, 0, bt->num_of_bits);
}

static bt_node_t *CreateNode()
{
	bt_node_t *node = (bt_node_t *)malloc(sizeof(*node));
	if(NULL == node)
	{
		return NULL;
	}
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
