// about strings (char arrays terminated by \0
// Version : 1.0
// Author : Team -C

main(){
	char a[5][10] = {"line one","line two","line three","line four","end"};
	char *k[] ={"one" ,"two","three","four"};
	char **ptr;
	int i;
	ptr = &k[0];
	for(i=0;i<3;i++){
		printf("%s\n",*ptr);
		ptr++;
	}	
}
