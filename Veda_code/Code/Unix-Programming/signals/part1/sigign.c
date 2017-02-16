/* Shows how to handle signals
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>


main(){
	/* install signal handlers for 1 , 2 and 3 */
	signal(1,SIG_IGN);
	signal(2,SIG_DFL);
	signal(SIGPIPE,SIG_DFL);
/* use macros instead of constants as signal numbers to improve redability */
	while(1){
		printf(" I am happy now , I will do same work forever\n");
	}
}
