/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 11/08/2019		*
*	 Reviewer: Inbar Madar     	*
*								*
*********************************/

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* size_t */
#include <assert.h> /* assert */

typedef struct c_queue c_queue_t;

/*Create the circular queue.
Return value: A pointer to the queue.
capacity must be larger then 0.*/
c_queue_t *QueueCreate(int capacity);

/*Destroy the queue.
queue != NULL.*/
void QueueDestroy(c_queue_t *queue);

/*Check if the queue is empty.
Return value: 1 if empty, 0 else.
queue != NULL*/
int QueueIsEmpty(const c_queue_t *queue);

/*Return value: The number of elements inside the queue.
queue != NULL*/
int QueueSize(c_queue_t *queue);

/*Return value: -1 if the queue is empty, else it returns the first element.
queue != NULL*/
int QueuePeek(const c_queue_t *queue);

/*Insert data to the queue.
queue != NULL*/
void QueueEnqueue(c_queue_t *queue, const int data);

/*Remove the last element from the queue.
Return value: 0 for success, -1 if the queue was empty
queue != NULL*/
int QueueDequeue(c_queue_t *queue);

/*Check if the queue is full.
Return value: 1 if full, 0 else.*/
int QueueIsFull(c_queue_t *queue);
