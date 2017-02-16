
/* Using execl 
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

main(){
	printf("Can you see me [ONE]\n");
	execl("./test","progname","arg1","arg2",NULL);	
	printf("Can you see me [TWO]\n");
}
