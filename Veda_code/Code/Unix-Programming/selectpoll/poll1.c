
/* Shows why we need to use select/poll for I/O multiplexing
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <poll.h>
# include <stropts.h>
# include <fcntl.h>

main(){
	int fd1,fd2;
	struct pollfd pollarray[10];
	char buf[10];
	int n;
	fd1 = open("./pone",O_RDWR);
	fd2 = open("./ptwo",O_RDWR);
	pollarray[0].fd = fd1;
	pollarray[1].fd = fd2;
	pollarray[0].events = POLLIN ;
	pollarray[1].events = POLLIN ;
	n = poll(pollarray,2,90000); 
	if (n <0 ){
		perror("poll:");
		exit(1);
	}
	printf("fd1 revent = %d\n",pollarray[0].revents);
	printf("fd2 revent = %d\n",pollarray[1].revents);
	printf("POLLIN %d\n",POLLIN);
	printf("POLLOUT %d\n",POLLOUT);
	printf(".. %d\n",(pollarray[0].revents & POLLIN));
	printf(".. %d\n",(pollarray[1].revents & POLLIN));
}
