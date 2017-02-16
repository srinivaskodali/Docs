/* Shows how to use Fork system call 
Version : 1.0
Author : Team -C
*/

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>

# define CHILD 0

main(){
       pid_t pid;	
	printf(" My pid = %d \n", getpid());
	getchar();
	pid = fork();
	if( pid == CHILD){
		printf(" child: My pid = %d \n", getpid());
		while(1);
	}
	// parent
	else{
		printf(" My pid = %d \n", getpid());
		printf(" Newly created child pid = %d \n", pid);
	}
}
		

