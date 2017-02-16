/* implementataion of queue Data Structure.
Version : 1.0
Author : Team -C
# include "queue.h"

extern int errno; // defined as part of libc implementataion.

QUEUE * init_queue( int size){
	QUEUE *q;
	q= (QUEUE *) malloc(sizeof(QUEUE));
	if(q == NULL)
		return NULL;
	q->size=size;
	q->elements = (int*) malloc(sizeof(int)*size);
	q->front=q->elements;
	q->rear=q->elements;
	q->end = q->elements + size;
	q->noe=0;
	if(q->elements ==NULL){
		free(q);
		return NULL;
}
void enqueue(QUEUE *q,int elem){
	int *temp,error=0;
	//check for queue is full or not
	if(q->noe==q->size){
		error=EQUE_FULL;
		printf("QUEUE is FULL\n");
		return;
		}
	*(q->rear)=elem;
	q->noe++;
	if(q->rear==q->end)
	q->rear=q->elements;
	else
	q->rear++;
	return;

	}
int dequeue(QUEUE *q){
	int item;
	int *temp;
	errno=0;
	if(q->noe==0){
		errno=EQUE_EMPTY;
		printf(" QUEUE Empty\n");
		return;
	}
	item =*(q->front);
	q->noe--;
	if(q->front == q->end)
		q->front= q->elements;
	else
		q->front++;
	return item;
}


// add the function destory_queue(QUEUE *q)
