#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
};

static struct Node *CreateNode(int data)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(*new_node));
	if(new_node == NULL)
	{
		return NULL;
	}

	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

static void PrintTree(struct Node *root)
{
	if (root == NULL)
	{
		return;
	}

	PrintTree(root->left);
	printf("%d->", root->data);
	PrintTree(root->right);
}

void MirrorBT(struct Node *root)
{
	struct Node *temp = NULL;

	if(root == NULL)
	{
		return;
	}

	MirrorBT(root->left);
	MirrorBT(root->right);	

	temp = root->left;
	root->left = root->right;
	root->right = temp;
}

int main()
{
	struct Node *root = CreateNode(4);
	root->left = CreateNode(2);
	root->right = CreateNode(5);
	root->left->left = CreateNode(1);
	root->left->right = CreateNode(3);

	MirrorBT(root);

	PrintTree(root);

	return 0;
}