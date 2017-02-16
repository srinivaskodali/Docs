
/* using sigset_t.
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <signal.h>

void check_blocked_sigs(){
	int i,res;
	sigset_t s;
	sigprocmask(SIG_BLOCK,NULL,&s); //first param is not considered
	for(i =1;i<5;i++){
		res = sigismember(&s,i);
		if(res)
			printf(" signal %d is blocked \n",i);
		else
			printf(" signal %d is not blocked \n",i);
	}
}
main(){
	sigset_t s_set;
	sigemptyset(&s_set);
	sigaddset(&s_set,1);
	sigaddset(&s_set,4);
	sigprocmask(SIG_BLOCK|SIG_SETMASK,&s_set,NULL);
	check_blocked_sigs();
	sigemptyset(&s_set);
	sigaddset(&s_set,2);
	sigprocmask(SIG_BLOCK,&s_set,NULL);
	check_blocked_sigs();
}
