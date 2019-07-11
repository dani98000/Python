struct node *RecFlipList(struct node *head)
{
	struct node *first = head;
	struct node *rest = NULL;
	
	if(head->next = NULL)
	{
		return head;
	}
	
	return RecFlipList(first->next);
	first->next->next = first;
	first->next = NULL
}
