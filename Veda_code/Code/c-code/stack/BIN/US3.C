
// To demonstrate how to use stack.
// Version : 1.0
// Author : Team -C

# include <stdio.h>
# include "stack1.h"

extern int stkerr; // defined some where.

main(){
	unsigned char c,x;
	int i;
	FILE *fp;
	init_stack();
	fp = fopen("abc.c","r");
	while( (i=fgetc(fp)) !=EOF ){
		c= (unsigned char) i;
		if ( (c == '{') || (c == '('))
			push(c); // add code to check for stack errors.
		if ( c == ')'){
			x=pop();
			if(x != '('){
				printf(" error in file \n");
				exit(-1);
			}
		}
		if ( c == '}'){
			x=pop();
			if(x != '{'){
				printf(" error in file \n");
				exit(-1);
			}
		}
	}
printf(" no error in file \n") ; // is it ???
	fclose(fp);
}

