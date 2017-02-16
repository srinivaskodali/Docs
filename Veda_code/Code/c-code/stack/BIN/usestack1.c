
// To demonstrate how to use stack.
// Version : 1.0
// Author : Team -C

# include <stdio.h>
# include "stack1.h"

extern int stkerr; // defined some where.
main(){
	char c;
	int i;
	init_stack();
	c=pop();
	printf(" stkerr = %d\n",stkerr);
	printf(" popped item = %c\n",c);
	c='a';
	for(i=0;i<11;i++){
		push(c+i);// we are storing a,b
		printf(" pushed %c ",c+i);
		printf(" stkerr = %d\n", stkerr);
	}
	getchar();
	for(i=0;i<11;i++){
		c=pop();
		printf(" stkerr = %d\n",stkerr);
		printf(" popped item = %c\n",c);
	}
}

