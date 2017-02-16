/ 
/* using sigset_t.
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <signal.h>

void sighand(int no){
	printf(" I am in sighandler\n");
}
main(){
	sigset_t s_set;
	signal(1,sighand);
	sigemptyset(&s_set);
	sigaddset(&s_set,1);
	perror("sig1");
	sigaddset(&s_set,4);
	perror("sig4");
	sigprocmask(SIG_BLOCK|SIG_SETMASK,&s_set,NULL);
	perror("sigmask");
	printf(" Send me signal one and see the effect now \n");
	getchar();
	getchar();
	sigprocmask(SIG_UNBLOCK,&s_set,NULL);
	printf(" Now signals are unblocked \n");
	while(1);
}
