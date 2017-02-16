/* test_char_driver_ioctl.c
Author:Team Veda
Version: 1.0
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "veda_char_device.h"

/**
* This program uses the device driver veda_chr_driver and opens a file on it.
* It performs the read, write and lseek operation apart from open() and close()
* Hence it checks the drivers functionality
*/
int main()
{
	int fd, i;
	char my_buf[4000];
	
	unsigned int size;
	char c;
	
	/* fill my buffer with *'s */
	for(i=0; i<4000; i++) my_buf[i] = '*';
	
	/* open the device for read/write/lseek */
	printf("[%d] - Opening device veda_cdrv\n", getpid() );
	fd = open( "/dev/veda_cdrv", O_RDWR );
	if( fd < 0 ) {
		printf("\n\nDevice could not be opened\n\n");
		return 1;
	}
	printf("Device opened with ID [%d]\n", fd);
	
	/* write the contents of my buffer into the device */
	write( fd, my_buf, 4000 );
	
	/* empty my buffer now */
	bzero(my_buf, 4000);
	
	/* read 70 characters from 20th character */
	lseek( fd, 20, SEEK_SET );
	read( fd, my_buf, 70 );
	printf("I read this from the device\n%s\n", my_buf);
	
	/* empty by buffer again */
	bzero(my_buf, 4000);
	
	/* Write something into the buffer */
	write( fd, "Veda Solutions", 14);
	
	/* Set the internal read/write pointer to th 60th character */
	lseek( fd, 60, SEEK_SET );
	
	/* read 70 characters from there and print it */
	read( fd, my_buf, 70 );
	printf("I read this from the device\n%s\n", my_buf);
	/* These were the operations that were working using 
	   char_driver.c and char_driver_devfs.c also */
	
	   
	/* Test cases for ioctl */
	lseek( fd, 0, SEEK_SET );
	/* Lets first resize our character buffer to 80 characters */
	ioctl( fd, VEDA_GET_SIZE, &size );
	printf("Present size of the buffer is %d\n", size);
	size = 4096;
	printf("Setting size of buffer to 4096\n");
	if( ioctl( fd, VEDA_SET_SIZE, &size ) < 0 )
		printf("ioctl failed\n");
	ioctl( fd, VEDA_GET_SIZE, &size );
	printf("New size of the buffer is %d\n", size);		

	
	/* lets fill the buffer with character '=' */
	bzero( my_buf, 4000 );
	read( fd, my_buf, 70 );
	printf("Current contents\n%s\nFilling ='s\n", my_buf);
	c = '=';
	ioctl(fd, VEDA_FILL_CHAR, &c);
	bzero( my_buf, 4000 );
	read( fd, my_buf, 70 );
	printf("New contents\n%s\n", my_buf);
	
	/* Close the device */
	close(fd);
	
	/* Thats all folks */
	exit(0);
}


