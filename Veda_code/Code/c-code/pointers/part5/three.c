
// shows how to use memory allocation functions
// Version : 1.0
// Author : Team -C

main(){
	int *ptr,*dummy;
	ptr = (int *) malloc(sizeof(int));
	dummy = (int *) malloc(sizeof(int));
	printf(" ptr = %x\n",ptr);
	printf(" dummy = %x\n",dummy);
	*ptr=1;
	printf(" *ptr = %d\n",*ptr);
	ptr = (int *) realloc(ptr,32);
	printf(" ptr = %x\n",ptr);
	printf(" *ptr = %d\n",*ptr);
}
