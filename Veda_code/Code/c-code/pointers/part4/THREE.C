// Demonstrates using pointers to structures
// Version : 1.0
// Author : Team -C

# include <stdio.h>

typedef struct emp{
	int empno;
	int sal;
	int deptno;
	struct emp *nextemp;
}Emp;
// Function used to store the list of employees to a linked list.
Emp * addEmpToList(Emp *top){
	Emp *temp;
	// let us go to end of the list so that we can add new emp
	// at the end of list.
	while(top->nextemp !=NULL)
		top=top->nextemp;
	temp=(Emp*) malloc(sizeof(Emp));
	if(temp == NULL)
		return temp;
	printf(" Enter empno:");
	scanf("%d",&temp->empno);
	printf(" Enter sal:");
	scanf("%d",&temp->sal);
	top->nextemp=temp;
	temp->nextemp=NULL;
	return temp;
}
void DisplayEmpList(Emp * top){
		printf("================\n");
	while( top->nextemp != NULL){
		top=top->nextemp;
		printf(" No = %d\n",top->empno);
		printf(" Sal =%d\n",top->sal);
		printf("================\n");
	}
}
main(){
	int noemp,i;
	Emp *top;
	top = (Emp*)malloc(sizeof(Emp));
	if(top==NULL){
		printf(" problem in allocation memory\n");
		exit(1);
	}
	top->nextemp=NULL;
	printf(" enter no of employees\n");
	scanf("%d",&noemp);
	for(i=0;i<noemp;i++)
		addEmpToList(top);
	DisplayEmpList(top);
}	
// add a function RemoveEmp( int empno) to the above program
