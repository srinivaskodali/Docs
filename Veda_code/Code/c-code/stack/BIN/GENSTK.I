# 1 "genstk.c"
 
 
 

# 1 "genstk.h" 1
 
 
 

 







void init_stack(void);
void push (int  item);
int  pop();
# 5 "genstk.c" 2



int stkerr;
static int  stack[10 ];
static int top;

 
void init_stack(void){
	top=-1;  
	stkerr=0;
}
 
void push(int  item){
	stkerr=0;
	 
	if(top == 10  -1){
		stkerr= -1 ;
		return;
	}
	top++;
	stack[top]=item;
}
 
 
int  pop(){
	int  item;
	stkerr=0;
	 
	if(top==-1){
		stkerr= -2 ;
		return '\0';  
	}
	item = stack[top];
	top--;
	return item;
}

