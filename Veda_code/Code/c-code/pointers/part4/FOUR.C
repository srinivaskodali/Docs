// Demonstrates using pointers to structures
// Version : 1.0
// Author : Team -C

# include <stdio.h>

typedef struct emp{
	int empno;
	int sal;
	int deptno;
	struct emp *nextemp;
	struct emp *prevemp;
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
		return top;
	printf(" Enter empno:");
	scanf("%d",&temp->empno);
	printf(" Enter sal:");
	scanf("%d",&temp->sal);
	top->nextemp=temp;
	temp->nextemp=NULL;
	temp->prevemp=top;
	return temp;
}
void displayFromTop(Emp * top){
		printf("================\n");
	while( top->nextemp != NULL){
		top=top->nextemp;
		printf(" No = %d\n",top->empno);
		printf(" Sal =%d\n",top->sal);
		printf("================\n");
	}
}
void displayFromBottom(Emp * bottom){
		printf("================\n");
	while( bottom->prevemp!= NULL){
		printf(" No = %d\n",bottom->empno);
		printf(" Sal =%d\n",bottom->sal);
		printf("================\n");
		bottom=bottom->prevemp;
	}
}
main(){
	int noemp,i;
	Emp *head;
	Emp *tail;
	head = (Emp*)malloc(sizeof(Emp));
	tail=head;
	if(head==NULL){
		printf(" problem in allocation memory\n");
		exit(1);
	}
	head->nextemp=NULL;
	head->prevemp=NULL;
	printf(" enter no of employees\n");
	scanf("%d",&noemp);
	for(i=0;i<noemp;i++)
		tail=addEmpToList(head);
	displayFromTop(head);
	printf(" List from Bottom \n");
        displayFromBottom(tail);
}	
// add a function RemoveEmp( int empno) to the above program
