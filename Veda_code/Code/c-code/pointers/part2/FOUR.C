// Program to implement a function which finds the length of stirng
// Version : 1.0
// Author : Team - C

// In this function we assume the the last string is "end"
int noofstr( char **ptrtostr){
	int nostrings=0;
	while ( strcmp(*ptrtostr,"end") !=0){
		nostrings++;
		ptrtostr++;
	}
	return nostrings;
}


main(){
	char *strings[10]={"abc","cdf","xyz","mno","end"};
	char *strings1[10]={"abc","mno","end"};
	char **s=strings;
	printf(" No Of Strings = %d\n",noofstr(s));
	printf(" No Of Strings = %d\n",noofstr(strings1));
	
}
// Test whether our function is fast or strlen is fast.
