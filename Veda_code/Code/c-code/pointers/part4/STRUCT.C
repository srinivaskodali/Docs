// Demonstrates using pointers to structures
// Version : 1.0
// Author : Team -C

typedef struct{
	int a;
	int b;
	int c;
}MyDT;
// In this case mydatatype becomes the name of new datatype
main(){
	MyDT m1;
	MyDT *ptr;
	m1.a=10;
	m1.b=20;
	m1.c=30;
	ptr=&m1;
	// we can now access the structure members as shown below.
	printf(" value of a = %d\n",(*ptr).a);
	printf(" value of b = %d\n",ptr->b); // we prefer using ->to access
					    // the member of the structure
					    // member using pointer.
	printf(" value of c = %d\n",ptr->c);
}	
