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
	int fd0,fd1,fd2, i,ret;
	char my_buf0[50] = "Hello World From veda_cdrv0";
	char my_buf1[50] = "Hello World From veda_cdrv1";
	char my_buf2[50] = "Hello World From veda_cdrv2";
	
	/* open the device for read/write/lseek */

	fd0 = open( "/dev/veda_cdrv", O_RDWR );
	fd1 = open( "/dev/veda_cdrv", O_RDWR );
	fd2 = open( "/dev/veda_cdrv", O_RDWR);

	/* try to read 40bytes from this device */
	if ((ret = write( fd0, my_buf0, strlen(my_buf0) )) < 0)
	{
		perror("\nWrite ");
	}
	
	printf("\n Written %d bytes to /dev/veda_cdrv0",ret);

	if ((ret = write( fd1, my_buf1, strlen(my_buf1) )) < 0)
	{
		perror("\nWrite");
	}
	printf("\n Written %d bytes to /dev/veda_cdrv1",ret);
	
	if ((ret = write( fd2, my_buf2, strlen(my_buf2) )) < 0)
	{
		perror("\nWrite ");
	}
	printf("\n Written %d bytes to /dev/veda_cdrv2",ret);

	/* Close the device */
	close(fd0);
	close(fd1);
	close(fd2);
}
