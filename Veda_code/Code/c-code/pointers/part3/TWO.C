
// shows how to use memory allocation functions
// Version : 1.0
// Author : Team -C

main(){
	void *p;
	int *ptr;
	p = (void *)malloc(4);
	ptr = (int *) p;
	printf(" ptr = %x\n",ptr);
	*ptr=9898;
	printf(" *ptr = %d\n",*ptr);
getchar();
}
