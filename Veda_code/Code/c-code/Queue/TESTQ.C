
/* program to test our queue
Version : 1.0
Author : Team -C
*/

# include "queue.h"
extern int errno;
main(){
	QUEUE * q;
	int it;
	q= init_queue(3);
	printf(" QUEUE = %x \n",q);
		it = dequeue(q);
	printf("errno = %d\n",errno);
	enqueue(q,10);
	enqueue(q,11);
	enqueue(q,12);
	printf(" elem = %d\n",dequeue(q));
	printf(" elem = %d\n",dequeue(q));
	printf(" elem = %d\n",dequeue(q));
		it = dequeue(q);
	printf("errno = %d\n",errno);
}
