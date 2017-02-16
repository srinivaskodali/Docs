
/* show how to  catch interrupt signal.
Version : 1.0
Author : Team -C
*/

# include <signal.h>

void sighand(int signum){
	printf("Interrupt signal rec'd \n");
}

main(){
	signal(SIGINT,sighand);
	while(1){
	}
}
