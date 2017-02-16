
/* program to test our queue
Version : 1.0
Author : Team -C
Remarks : With this queue implementation we can create any no of
Queues as part of our Application.
*/

# include "queue.h"
extern int errno;
main(){
	QUEUE * q;
	int it;
	q= init_queue(3);
	printf(" QUEUE = %x \n",q);
	enqueue(q,1);
	enqueue(q,11);
	enqueue(q,12);
	printf(" elem = %d\n",dequeue(q));
	printf(" elem = %d\n",dequeue(q));
	enqueue(q,13);
	printf(" elem = %d\n",dequeue(q));
	printf(" elem = %d\n",dequeue(q));
	enqueue(q,19);
	printf(" elem = %d\n",dequeue(q));
	it = dequeue(q);
}
