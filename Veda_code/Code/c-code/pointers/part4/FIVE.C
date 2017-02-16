// Demonstrates Hashing without chaining
// Version : 1.0
// Author : Team -C

# include <stdio.h>
# define TABSIZE 10

typedef struct emp{
	char *name;
	int empno;
	int sal;
	int deptno;
}Emp;

Emp *EmpHashTable[TABSIZE];

// hashcode function computes a no which will be used as an index into 
// hash table. We can use any algorithm to compute hashcode. Here we
// are  using a simple algorithm for this.
int hashcode( char * name){
	int code=0;	
	while(*name != '\0'){
		code +=*name;
		name++;
	}
	return code;
}
void addtoEmpTable(){
	char c[100];
	int hashcd;
	Emp * temp;
	printf(" Enter Employee Name:");
	scanf("%s",c);
	hashcd=hashcode(c);
	printf(" Hash Code =%d \n",hashcd);
	hashcd = hashcd % TABSIZE;
	printf(" Hash Code =%d \n",hashcd);
	if(EmpHashTable[hashcd] !=NULL){
		printf(" Already an employee with same hash code exists\n");
		return;
	}
	temp = (Emp *) malloc(sizeof(Emp)); // check for NULL
	printf(" Enter no :");
	scanf("%d",&temp->empno);
	// memcpy(dest,source,count);
	temp->name = (char*) malloc(strlen(c)+1);
	memcpy(temp->name,c,strlen(c) + 1);
	EmpHashTable[hashcd]=temp;
	printf("%s Info Stored\n",EmpHashTable[hashcd]->name);
}	

main(){
	int noemp,i;
	for( i =0 ; i<TABSIZE;i++)
		EmpHashTable[i]=NULL;
	printf(" Enter no of employees:");
	scanf("%d",&noemp);
	for(i=0;i<noemp;i++)
		addtoEmpTable(); 
}	
// add code for the following function 
// ListEmpInTable()
// DisplayEmpInfo(String *name)
