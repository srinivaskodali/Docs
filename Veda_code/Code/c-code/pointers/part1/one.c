// shows how to use a pointer to pointer.
// veriosn : 1.0
// Author : Team -C

main(){
	int *ptr;
	int **ptrtoptr;
	int p;
	p=9;
	ptr=&p;
	ptrtoptr=&ptr;
	printf(" adress of ptr = %x\n",ptrtoptr);
	printf(" adress of ptrtoptr = %x\n",&ptrtoptr);
	printf(" adress of p = %x\n",ptr);
	printf( " content of *ptr = %x\n",*ptr);
	printf( " content of *ptrtoptr = %x\n",*ptrtoptr);
	printf( " content of **ptrtoptr = %x\n",**ptrtoptr);
}
