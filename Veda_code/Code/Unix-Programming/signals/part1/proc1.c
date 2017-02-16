/* show How the process can be terminated 
Version: 1.0
Author : Team -C
*/
main(int argc, char *argv[]){
	int no,c=1;
	printf("No of args passed = %d\n",argc);
	for(no=0;no<argc;no++)
		printf("%s\n",argv[no]);
	printf(" This is the first line \n");
	printf(" enter a no :");
	scanf("%d",&no);
	if(no <5)
		exit(0);
	while(c){
		printf(" I will continue forever \n");
	}
	printf(" Last line of main\n");
}
/* process gets terminated when it executes exit or when the main function 
returns or when it receives a signal which is not handled ?
*/
