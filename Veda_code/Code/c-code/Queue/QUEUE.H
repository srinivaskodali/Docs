/* constants and function proto's of used by queue datastructure.
Version : 1.0
Author : Team -C
Remarks : data elements stored in this queue is of type int's , you can
customize the code according to the needs
*/

# include <stdio.h>
# define EQUE_FULL -1
# define EQUE_EMPTY -2

typedef struct queue{
	int *rear;
	int *front;
	int size;
	int * elements; // we can use different datatypes for this
	int * end;
	int noe;
}QUEUE;
// not all the above fields are required, try to reduce the no of
// fields to maintain the information about the queue.
QUEUE * init_queue( int size);
void enqueue(QUEUE *q,int item);
int dequeue(QUEUE *q);

