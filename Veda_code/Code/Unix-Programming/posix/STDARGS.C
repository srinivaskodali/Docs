
/* show how to write a variable argument function like printf
using ansi -c stdarg.h 
Version : 1.0
auhtor : Team -C
*/
# include <stdio.h>
# include <stdarg.h>
/* for varargument functions there must be atleast one named arg
programmer writting these kind of function has to have a means of 
finding the no of args passed.
*/

int varargfn(int i,...){
	va_list arg_ptr;
	int k,val;
	va_start(arg_ptr,i);
	for(k=0;k<i;k++){
		val = va_arg(arg_ptr,int);
		printf(" Parameter = %d \n",val);
	}
}

main(){
	printf("===============\n");
	varargfn(2,34,34);
	printf("===============\n");
	varargfn(4,4,4,4,4);
}
