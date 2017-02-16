/* This example is used to demonstrate how to detact overruns.
Version: 1.0
Author : Team -C
Remarks : build executable by linking application with efence library
using gcc -ggdb overrun.c -lefence -o overrun
After compiling we need to run our program using gdb overrun
*/
void buggyfunction(){
	int * intptr;
	int i;
// we are allocating memory to hold only 4 integers in this program.
	intptr = (int *) malloc( sizeof(int) *4);
	for(i=0;i<2;i++){
		*intptr = 55;
		intptr--;
	}
// we are trying to access memory which is not allocated by us here.
}

// our main function is used to test the buggyfunction here.
main(){
	buggyfunction();
}

// to detect underruns we need to set env variable EF_PROTECT_BELOW=1
