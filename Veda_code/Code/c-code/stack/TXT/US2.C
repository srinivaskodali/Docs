
// To demonstrate how to use stack.
// Version : 1.0
// Author : Team -C

# include <stdio.h>
# include "stack1.h"

extern int stkerr; // defined some where.

main(){
	unsigned char c;
	int i;
	FILE *fp;
	init_stack();
	fp = fopen("abc.c","r");
	while( (i=fgetc(fp)) !=EOF ){
		c= (unsigned char) i;
		printf("%c",c);
	}
	fclose(fp);
}

