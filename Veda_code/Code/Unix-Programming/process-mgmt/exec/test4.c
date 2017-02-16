
/* To test whether the new process that replaces old one will
inherit the fd's or not.
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

main(){
	printf(" Can you see this \n");
	perror("Can you see this...");
}
