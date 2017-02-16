/* Shows how to handle signals
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>

static int one_occured = 0;
static int tt_occured = 0;
/* below is the handler for signal 1 */

void  sh_for_one( int signum){
	one_occured = 1;
	printf(" This is handler for signal no one \n");
}

/* below is the handler for signal's 2 and 3*/
void  sh_for_tt( int signum){
	tt_occured =1;
	printf(" I am now handling signal no %d \n",signum);
}

main(){
	/* install signal handlers for 1 , 2 and 3 */
	signal(1,sh_for_one);
	signal(2,sh_for_tt);
	signal(3,sh_for_tt);
/* use macros instead of constants as signal numbers to improve redability */
	while(1){
		printf(" I am happy now , I will do same work forever\n");
		if(one_occured)
			goto bad_work;
	}
bad_work:
	while(1){
		printf(" I am doing bad work for my survival\n");
		if(tt_occured)
			goto die;
	}
die:
	while(1){
		printf(" I am going to die some day \n");
	}
}
