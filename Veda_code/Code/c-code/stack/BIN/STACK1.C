// Module implementing stack.
// Version : 1.0
// Author : Team -C

# include "stack1.h" 


int stkerr;
static char stack[STACK_SIZE];
static int top;

// function to initialize stack
void init_stack(void){
	top=-1; // to indicate that there is nothing in stack
	stkerr=0;
}
// to push an item on stack. Can you see any bug here ???
void push(char item){
	stkerr=0;
	// check if stack is full or not.
	if(top == STACK_SIZE -1){
		stkerr=ERR_FULL;
		return;
	}
	top++;
	stack[top]=item;
}
// to get an item from stack.
// caller of this function should first check for error                                                                                                                                                                                                                                                                     
	char item;                                                       
	stkerr=0;
	// check if stack is empty
	if(top==-1){
		stkerr=ERR_EMPTY;
		return '\0'; // bad choice.
	}
	item = stack[top];
	top--;
	return item;
}

