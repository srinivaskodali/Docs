/* code for reader 1 and reader 2 are one and the same 
Author:Team C
Version:1.0
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "veda_char_device.h"
int main()
{
	int fd, i,ret;
	char my_buf[4000];
	
	bzero(my_buf, 4000);
		
	/* open the device for read/write/lseek */
	printf("[%d] - Opening device veda_cdrv\n", getpid() );
	fd = open( "/dev/veda_cdrv", O_RDONLY );
	perror("fd ");
	if( fd < 0 ) {
		printf("Device could not be opened\n");
		return 1;
	}
	printf("Device opened with ID [%d]\n", fd);

	
	/* try to read 40bytes from this device */
	printf("Trying to read from the device\n\n");
	if ((ret = read( fd, my_buf, 20 )) < 0)
	{
		perror("\nRead ");
		exit(1);
	}

	printf("Read [%s]\n", my_buf);
	//ioctl(fd,VEDA_FILL_ZERO);
	
	/* Close the device */
	close(fd);
	
	/* Thats all folks */
	//exit(0);
}


