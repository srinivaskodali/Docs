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
	struct emp *next;
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
	Emp * temp,*dummy;
	printf(" Enter Employee Name:");
	scanf("%s",c);
	hashcd=hashcode(c);
	hashcd = hashcd % TABSIZE;
	temp = (Emp *) malloc(sizeof(Emp)); // check for NULL
	printf(" Enter no :");
	scanf("%d",&temp->empno);
	// memcpy(dest,source,count);
	temp->name = (char*) malloc(strlen(c)+1);
	memcpy(temp->name,c,strlen(c) +1);
	temp->next=NULL;
	if(EmpHashTable[hashcd] == NULL)
		EmpHashTable[hashcd] = temp;
	else{
		dummy = EmpHashTable[hashcd];
		while(dummy ->next != NULL)
			dummy = dummy->next;
		// we are now at the end of list.
		dummy->next = temp;
		printf(" Collision Resolved by using Chaining\n");
	}
	printf("%s Info Stored\n",EmpHashTable[hashcd]->name);
}	
void DisplayHT(){
	int i;
	Emp *dummy;
printf("===================================\n");
	for(i =0; i<TABSIZE;i++){
	 printf("%d  ",i);
	 dummy = EmpHashTable[i];
		while(dummy!=NULL){
			printf("%s ",dummy->name);
			dummy=dummy->next;
		}
	 printf("\n");
	}
printf("===================================\n");
}
main(){
	int noemp,i;
	for( i =0 ; i<TABSIZE;i++)
		EmpHashTable[i]=NULL;
	printf(" Enter no of employees:");
	scanf("%d",&noemp);
	for(i=0;i<noemp;i++)
		addtoEmpTable(); 
	DisplayHT();
}	
// add code for the following function 
// DisplayEmpInfo(String *name)
