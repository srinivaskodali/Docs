// general technique used to store array of strings and manuplate it. 
// Version : 1.0
// Author : Team -C

main(){
//	char *k[] ={"one" ,"two","three","four","end"};
	char *k[] ={"one" ,"four","end"};
	char **ptr;
	int i;
	ptr = &k[0];
	while(strcmp(*ptr,"end")!=0){
		printf("%s\n",*ptr);
		ptr++;
	}	
}
