







/* shows how to use exec call.
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>

char *argstochild[10];
char *envofchild[10];

void prepare_args(){
	argstochild[0] = (char *) malloc(20);
	strcpy(argstochild[0],"./progname"); 
	argstochild[1] = (char *) malloc(20);
	strcpy(argstochild[1],"param1"); 
	argstochild[2] = (char *) malloc(20);
	strcpy(argstochild[2],"param2"); 
	argstochild[3]=NULL;
}

void prepare_env(){
	envofchild[0] = (char *) malloc(20);
	strcpy(envofchild[0],"env1=value1"); 
	envofchild[1] = (char *) malloc(20);
	strcpy(envofchild[1],"env1=value1"); 
	envofchild[2]=NULL;
}
main(){
	printf("Can you see me [ONE]\n");
	prepare_args();
	prepare_env();
	execve("./test1",argstochild,envofchild);	
	printf("Can you see me [TWO]\n");
}
