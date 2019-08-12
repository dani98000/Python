#include <stdio.h>

#include "circular_queue.h"

void DisplayQueue(c_queue_t *queue)
{
	while(!QueueIsEmpty(queue))
	{
		printf("%d,", QueuePeek(queue));
		QueueDequeue(queue);
	}
}

int main()
{
	c_queue_t *queue = QueueCreate(5);

	printf("Queue Size: %d\n", QueueSize(queue));
	QueueEnqueue(queue, 1);
	printf("Queue Size after 1 insert: %d\n", QueueSize(queue));
	printf("%d\n", QueuePeek(queue));
	
	QueueEnqueue(queue, 2);
	printf("Queue Size after 2 insert: %d\n", QueueSize(queue));

	QueueEnqueue(queue, 3);
	printf("Queue Size after 3 insert: %d\n", QueueSize(queue));

	QueueEnqueue(queue, 4);
	printf("Queue Size after 4 insert: %d\n", QueueSize(queue));

	QueueEnqueue(queue, 5);
	printf("Queue Size after 5 insert: %d\n", QueueSize(queue));

	QueueDequeue(queue);
	printf("Queue Size after 1 dequeue: %d\n", QueueSize(queue));

		QueueEnqueue(queue, 5);
	printf("Queue Size after 5 insert: %d\n", QueueSize(queue));


	DisplayQueue(queue);
	QueueDestroy(queue);

	return 0;
}