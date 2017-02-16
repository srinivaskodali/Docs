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
	char my_buf[4000];
	
	bzero(my_buf, 4000);
		
	/* open the device for read/write/lseek */
	fd0 = open( "/dev/veda_cdrv", O_RDONLY );
	fd1 = open( "/dev/veda_cdrv", O_RDONLY );
	fd2 = open( "/dev/veda_cdrv", O_RDONLY );

	/* try to read 40bytes from this device */
	printf("Trying to read from the veda_cdrv devices\n\n");
	if ((ret = read( fd0, my_buf,50 )) < 0)
	{
		perror("\nRead ");
	}
	printf("Read from veda_cdrv0 [%s]\n", my_buf);

	if ((ret = read( fd1, my_buf, 50 )) < 0)
	{
		perror("\nRead ");
	}
	printf("Read from veda_cdrv1 [%s]\n", my_buf);

	
	if ((ret = read( fd2, my_buf, 50 )) < 0)
	{
		perror("\nRead ");
	}
	printf("Read from veda_cdrv2 [%s]\n", my_buf);


	/* Close the device */
	close(fd0);
	close(fd1);
	close(fd2);
	
	/* Thats all folks */
	//exit(0);
}


