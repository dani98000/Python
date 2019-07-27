#include "ip.h"


typedef struct bt_node
{
	size_t is_full;
	bt_node_t *children[2]
} bt_node_t;

typedef struct bt
{
	size_t num_of_bits;
	bt_node_t *root;
} bt_t;

bt_t BTCreate(size_t num_of_bits);
void BTDestroy(bt_t *trie);
int BTInsert(bt_t *trie, uint_32 data)