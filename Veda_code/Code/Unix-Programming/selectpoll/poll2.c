
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
	// test whether fd1 is ready or not
	if((pollarray[0].revents & POLLIN) == 1 ){
		printf(" reading from fd1 (pone)\n");
		n = read(fd1,buf,10);
		printf(" read %d from pone \n",n);
	}
	// test whether fd2 is ready or not
	if((pollarray[1].revents & POLLIN) == 1 ){
		printf(" reading from fd2 (ptwo)\n");
		n = read(fd2,buf,10);
		printf(" read %d from ptwo \n",n);
	}
}
