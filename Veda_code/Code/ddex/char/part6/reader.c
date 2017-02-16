/* code for reader 1 and reader 2 are one and the same 
** Team: Veda
**Version: 1.0
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int fd;
char my_buf[4000];

/* signal handler that is called when sigio is got */
void handler(int sig)
{
	printf("Got SIGIO\n");
	/* try to read 40bytes from this device */
	printf("Trying to read from the device\n");
	read( fd, my_buf, 20 );
	printf("Read [%s]\n", my_buf);
}

int main()
{
	int i, oflags;
	char cmd[250];
	
	bzero(my_buf, 4000);

	/* open the device for read/write/lseek */
	printf("[%d] - Opening device veda_cdrv\n", getpid() );
	fd = open( "/dev/veda_cdrv", O_RDWR );
	if( fd < 0 ) {
		printf("Device could not be opened\n");
		return 1;
	}
	printf("Device opened with ID [%d]\n", fd);

	fcntl(fd, F_SETOWN, getpid()); /* set this process as owner */
	oflags = fcntl(fd, F_GETFL); /* get file flags now */
	fcntl(fd, F_SETFL, oflags|FASYNC); /* enable async notice */		
	signal(SIGIO, handler); /* install signal handler */
	
	printf("I will now behave like a shell\n");
	while(1) {
		bzero(cmd, 350);
		printf("\nEnter Command: ");
		gets( cmd );
		if( !strcmp("exit", cmd) ) break;
		system( cmd );
	}
	printf("Bye\n");
	
	/* Close the device */
	close(fd);
	
	/* Thats all folks */
	exit(0);
}


