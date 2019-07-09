enum children{LEFT, RIGHT};

typedef struct avl_node
{
	void *data;
	struct avl_node children[2];
	size_t height;
}avl_node_t;

struct avl
{
	avl_node_t *root;
	avl_cmp_f compare;
	const void *params;
};

static CreateNode(void *data);
static avl_node_t *SameSideRotataion(avl_node_t *root ,int side);
static int GetBalanceFactor(avl_node_t *root);

avl_t *AVLCreate(avl_cmp_f compare, const void *params)
{
	avl_t *avl = NULL
	
	assert(NULL != data);
	
	avl = (avl_t *)malloc(sizeof(avl_t));
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
	avl_node_t *current = NULL;
	int res = 0;
	int balance_factor = 0;
	
	assert(NULL != current);
	
	current = root;
	
	res = avl->compare(current->data, data, NULL);
	
	if(AVLIsEmpty(avl))
	{
		CreateNode(data);
	}
	if(res > 0)
	{
		current->children[LEFT] = AVLInsert(current->children[LEFT], key);
	}
	if(res < 0)
	{
		current->children[RIGHT] = AVLInsert(current->children[left], key);
	}
	
	balance_factor = GetBalanceFactor(current);
	current->height = GetMaxHeight(current) + 1;
	
		
}

static int GetMaxHeight(avl_node_t node)
{
	size_t r_child_height = node->children[RIGHT]->height;
	size_t l_child_height = node->children[LEFT]->height;
	
	return r_child_height > l_child_height ? r_child_height : l_child_height 
}

static avl_node_t *SameSideRotataion(avl_node_t *root ,int side)
{
	int other_side = side == LEFT;
	avl_node_t *pivot_child = pivot->children[other_side];
	avl_node_t *pivot = root->children[side];
	
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
	
	assert(NULL != data)
	
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

static int CompareGetSide()

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
