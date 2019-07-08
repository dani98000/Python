#include "stack.h" /* stack header file */

struct node
{
	struct node *next;
	void *data;
};

typedef struct node node_t;

int FibRec(int n);
int FibIter(int n);
int str_len(char *str);
int str_cmp(char *str1, char *str2);
char *str_cpy(char *dest, const char *src);
node_t *RecurFlip(node_t *head);


