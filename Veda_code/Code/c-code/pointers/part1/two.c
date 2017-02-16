// shows how to use a pointer to pointer.
// veriosn : 1.0
// Author : Team -C

main(){
	int *ptr;
	int **ptrtoptr;
	int x,p;
	p=9;
	ptr=&p;
	ptrtoptr=&ptr;
	(**ptrtoptr)++;
	printf(" value of **ptrtoptr = %d\n",**ptrtoptr);
	printf( "ptrtoptr = %x\n",ptrtoptr);
	ptrtoptr++;
	printf( "ptrtoptr = %x\n",ptrtoptr);
	ptrtoptr--;
	printf(" ptr = %x\n",ptr);
	(*ptrtoptr) ++;
	printf(" ptr = %x\n",ptr);
	(*ptrtoptr) --;
	x=**ptrtoptr;
	printf( "ptrtoptr = %x  x=%d\n",ptrtoptr,x);
	x=++**ptrtoptr;
// never use the constructs like above .
	printf( "ptrtoptr = %x  x=%d\n",ptrtoptr,x);
}
