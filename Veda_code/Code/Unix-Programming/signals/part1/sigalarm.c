
/* show how to perform some task periodically 
Version : 1.0
Author : Team -C
*/

# include <signal.h>

void sighand(int signum){
	printf(" I have to wake up my boss now\n");
	alarm(5);
}

main(){
	signal(SIGALRM,sighand);
	alarm(5);
	while(1){
	}
}
/* check manual for info on setitimer function */
