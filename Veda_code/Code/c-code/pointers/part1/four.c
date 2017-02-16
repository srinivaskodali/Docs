// about strings (char arrays terminated by \0
// Version : 1.0
// Author : Team -C

	char *k[] ={"one" ,"two","three","four"};
main(){

	char a[5][10] = {"line one","line two","line three","line four","end"};
	int i;
	for(i=0;i<3;i++){
		printf(" k[%d] = %x \n",i,k[i]);
		printf("%s\n",k[i]);
	}	
}
