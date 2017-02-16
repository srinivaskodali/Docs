/* Shows how to use Fork system call 
Version : 1.0
Author : Team -C
*/

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>

# define CHILD 0
void sighand(int signum){
	printf(" I am in sig handler \n");
}

main(){
        pid_t pid;	
	int childstatus;
	pid = fork();
	if( pid == CHILD){
		while(1); // infinite loop.
	}
	// parent
	else{
		signal(1,sighand);
		wait(&childstatus);
		if(WIFSIGNALED(childstatus)){
			printf(" child was killed due to uncaught sig\n");
		}
	}
}
		

