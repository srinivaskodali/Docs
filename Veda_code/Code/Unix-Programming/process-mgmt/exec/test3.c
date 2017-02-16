
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
	int fd = open("./exec1.c",O_RDONLY);
	printf("in test3 fd = %d\n",fd);
}
