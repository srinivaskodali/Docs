
/*
 * 	Application reads data for Read.txt file and write to Write.txt file asynchronously
 * 	Author: Team Veda
 * 	linux-2.6.25-i386
 * 	version: 1.0
 *
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <aio.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFER_SIZE  100
#define MAX 3

/* Function to fill the aiocb values */
void populate_aiocb(struct aiocb *aio, int fd, off_t offset, int bytes, char *buf){
        aio->aio_fildes = fd;
        aio->aio_offset = offset;
        aio->aio_nbytes = bytes;
        aio->aio_buf = buf;
}

int main(){
	
	struct aiocb a_write, a_read;
	struct aiocb *cblist[MAX];
	int err_r, err_w;
	int read_n = 0;
	int fd;
	char read_buf[BUFFER_SIZE];
	char write_buf[BUFFER_SIZE];
	
	/* Open Temp.txt file for reading & writing */
	fd = open("Temp.txt", O_CREAT | O_RDWR, 0644);

	/* Its good practice to clear the aiocbs before 
	 * using them
	 */
	memset(&a_write, 0 , sizeof(struct aiocb));
	memset(&a_read, 0 , sizeof(struct aiocb));


	/* populate aiocbs to defaults */
	populate_aiocb(&a_read, fd, 0, BUFFER_SIZE-1, read_buf);
	populate_aiocb(&a_write, fd, 0, BUFFER_SIZE-1, write_buf);

	/* Start async read. The function will read a_read.aio_nbytes bytes
	 * from file a_read.aio_fildes starting from a_read.aio_offset into 
	 * buffer a_read.aio_buf. On success 0 is returned. This function will
	 * return immediately after queueing the request
	*/
	printf("\n Enter Data for writing into the file\n");
	while(1)
	{
		scanf("%100s",write_buf);
		if(strcmp(write_buf,"EOF")==0)
			break;
		aio_write(&a_write);
		/* After starting any async operation (read or write), you can get its status
		 * using aio_error function. This function returns EINPROGRESS if the request has not been completed
                 * It  returns ECANCELED if the request was cancelled.It returns 0
                 * if the request completed successfully.  Otherwise  an  error  value  is returned
                */
		if(err_r = aio_error(&a_write) == EINPROGRESS){
                        /* The  aio_suspend  function  suspends the calling process until at least
                         * one of the asynchronous I/O requests in the list  cblist have completed,
                         * a signal is delivered, or timeout occurs. Here we are waiting for
                         * aio_read completion on a_read.
                        */
                        cblist[0] = &a_write;
		/* aio_error returns 0 that is success. Call aio_return to find of number of
 		 * bytes read. The function should be called only once after aio_error returns
                 * something other than EINPROGRESS.
                */
                        aio_suspend(cblist, 1, NULL);
                }
		// Update write offset
		a_write.aio_offset += aio_return(&a_write);
	}
	
	lseek(fd,0,SEEK_SET);
	
	printf("\n Data in Temp.txt file\n");
	while(1)
	{
		aio_read(&a_read);
	
		if(err_r = aio_error(&a_read) == EINPROGRESS){
			cblist[0] = &a_read;
			aio_suspend(cblist, 1, NULL);
		}
		read_n  = aio_return(&a_read);
		printf("\n %s ",read_buf);			
		if(read_n!=BUFFER_SIZE-1)
			break;
		else
		{
			/* update read  offset */
			a_read.aio_offset += read_n;
		}
	}
	close(fd);

}
