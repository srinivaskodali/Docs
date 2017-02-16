
/* code for reader 1 and reader 2 are one and the same */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
	int fd, i;
	char my_buf[4000];
	
	bzero(my_buf, 4000);
		
	/* open the device for read/write/lseek */
	printf("[%d] - Opening device veda_cdrv\n", getpid() );
	fd = open( "/dev/veda_cdrv", O_RDWR );
	if( fd < 0 ) {
		printf("Device could not be opened\n");
		return 1;
	}
	printf("Device opened with ID [%d]\n", fd);

	
	/* try to read 40bytes from this device */
	printf("Trying to read from the device\n");
	read( fd, my_buf, 20 );
	printf("Read [%s]\n", my_buf);
	
	/* Close the device */
	close(fd);
	
	/* Thats all folks */
	exit(0);
}


