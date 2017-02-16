// Demonstrates using pointers to structures
// Version : 1.0
// Author : Team -C

typedef struct abc{
	int a;
	int b;
	int c;
	struct abc *ptr;
}MyDT;
// In this case mydatatype becomes the name of new datatype
main(){
	MyDT m1;
	m1.a=10;
	m1.b=20;
	m1.c=30;
	m1.ptr=&m1;
	printf(" value of a = %d\n",(*m1.ptr).a);
	printf(" value of b = %d\n",m1.ptr->b); // we prefer using ->to access
					    // the member of the structure
					    // member using pointer.
	printf(" value of c = %d\n",m1.ptr->c);
}	
