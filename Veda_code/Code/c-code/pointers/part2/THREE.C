// Program to implement a function which finds the length of stirng
// Version : 1.0
// Author : Team - C

int lenofstr( char *ptrtostr){
	int len=0;
	while(*ptrtostr !='\0'){
		len++;
		ptrtostr++;
	}
	return len;
}


main(){
	char *s = "this is a string";
	char *s1 = " This is another String";
	printf(" %d\n",s);
	printf(" length of first String = %d\n", lenofstr(s));
	printf(" length of second String = %d\n", lenofstr(s1));
	printf(" length of Third String = %d\n", lenofstr("xyz"));
}
// Test whether our function is fast or strlen is fast.
