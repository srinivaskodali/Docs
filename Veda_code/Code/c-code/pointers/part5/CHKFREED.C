/* This example is used to demonstrate how to detect access to freed
areas.
Version: 1.0
Author : Team -C
Remarks : build executable by linking application with efence library
using gcc -ggdb overrun.c -lefence -o overrun
After compiling we need to run our program using gdb overrun
*/
void buggyfunction(){
	int * intptr;
	intptr = (int *) malloc( sizeof(int));
	*intptr=55;
	printf("  intptr points to %x\n",intptr);
	free(intptr);
	printf("  intptr points to %x\n",intptr);
	*intptr=99; // common mistake !!!
// we are trying to access memory which is not allocated by us here.
}

// our main function is used to test the buggyfunction here.
main(){
	buggyfunction();
}

