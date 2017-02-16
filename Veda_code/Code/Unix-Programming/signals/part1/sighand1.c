/* Shows how to handle signals
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
/* sig hand for one */

void  sh_for_one( int signum){
	printf(" This is handler for signal no one \n");
}

/* below is the handler for signal's 9*/
void  sh_for_nine( int signum){
	printf(" I am now handling signal no %d \n",signum);
}

main(){
	/* install signal handlers for 1 , 2 and 3 */
	signal(1,sh_for_one);
	signal(SIGKILL,sh_for_nine);
	perror("siginstall:");
	getchar();
	getchar();
/* use macros instead of constants as signal numbers to improve redability */
	while(1){
		printf(" I am happy now , I will do same work forever\n");
	}
}
