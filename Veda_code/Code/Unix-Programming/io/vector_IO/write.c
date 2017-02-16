
/*
 * 	Application writes data into Write.txt file from multiple buffers 
 * 	Author: Team Veda
 * 	linux-2.6.25-i386
 * 	version: 1.0
 *
*/
#include <stdio.h>
#include <string.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE  100
#define MAX 3

/* Function to fill the iovec values */
void populate_iovec(struct iovec *iovec,char *ptr, int size){
	iovec->iov_base = ptr;
        iovec->iov_len = size;
}

int main(){
	
	int fd,wbytes;	
	char write_buf1[BUFFER_SIZE] = " The writve() function shall be equivalent to write(). ";
	char write_buf2[BUFFER_SIZE] = " The writev() function writes iovcnt buffers of data described ";
	char write_buf3[BUFFER_SIZE] = " by iov to the file associated with the ";
	char write_buf4[BUFFER_SIZE] = " file  descriptorfd.\n ";
	struct iovec iovec[4];
	

	/* Open Write.txt file for writing */
	fd = open("Write.txt", O_CREAT | O_WRONLY ,0644);

	populate_iovec(iovec,write_buf1,strlen(write_buf1));	
	populate_iovec(iovec+1,write_buf2,strlen(write_buf2));	
	populate_iovec(iovec+2,write_buf3,strlen(write_buf3));	
	populate_iovec(iovec+3,write_buf4,strlen(write_buf4));	

	/* The writev() function writes iovcnt buffers of data to the 
 	*  file associated with the  file  descriptor
 	*/
	wbytes = writev(fd, iovec, sizeof(iovec) / sizeof(struct iovec));
	printf("\n Total number of bytes written inti file : %d \n",wbytes);
	close(fd);

}
