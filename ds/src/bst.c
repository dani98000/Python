static bst_it_t BSTCreateNode(void *data, bst_it_t parent, bst_it_t children[LEFT], bst_it_t children[RIGHT])
{
	bst_it_t node = (bst_it_t)malloc(sizeof(struct bst_node));
	
	if(NULL == node)
	{
		free(node);
		return NULL;
	}
	
	node->data = (void *)data;
	node->parent = parent;
	node->children[LEFT] = children[LEFT];
	node->children[RIGHT] = children[RIGHT];
	
	return node;
}

static bst_it_t *InOrder(bst_it_t iter, int side)
{
	bst_it_t *iter_parent = NULL;
	bst_it_t *child = NULL;
	
	iter_parent = iter->parent;
	if(iter->children[side] == NULL)
	{
		while(iter_parent->children[side] == iter)
		{
			iter_parent = iter_parent->parent;
			iter = iter->parent;
		}
		return iter_parent;
	}
	else
	{
		child = iter->children[side];
		while(child->children[side] != NULL)
		{
			child = child->children[side];
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
	
	bst->dummy = BSTCreateNode((void *)0xDEADBEEF, NULL, NULL);
	bst->compare = compare;
	bst->params = params;
	
	return bst;
}

bst_it_t BSTInsert(bst_t *bst, void *data)
{
	bst_it_t *iter= NULL;
	bst_it_t *runner = BSTBegin(bst);
	
	if(BSTIsEmpty(bst))
	{
		iter = BSTCreateNode(data, bst->dummy, NULL, NULL);
		bst->children[left] = iter; 
	}
	else if(data > BSTBegin(bst)->data)
	{ 
		while(data > runner->data)
		{	
			runner = BSTNext(bst);
		}
		while(runner->parent->children[LEFT] )
		{
			
		}
		

 
    return node; 
} 

bst_it_t BSTBegin(const bst_t *bst)
{
	assert(NULL != bst);

	return bst->children[LEFT];
}

bst_it_t BSTEnd(const bst *bst)
{
	assert(NULL != bst);
	
	return bst->dummy;
}

int BSTIsEmpty(const bst_t *bst)
{
	return !(bst->Children[LEFT] == NULL);
}

/* return NULL if  there is no Prev */
bst_it_t BSTPrev(bst_it_t node)
{
	bst_it_t res = InOrder(node, LEFT);
	if(res != node)
	{
		return res;
	}
	return NULL;
}
/* return NULL if  there is no Next */
bst_it_t BSTNext(bst_it_t node)
{
	return InOrder(node, RIGHT);
}
