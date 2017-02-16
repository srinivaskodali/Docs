
/*
 * 	Application reads data for Read.txt file and write to Write.txt file asynchronously
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
void populate_aiocb(struct aiocb *aio, int fd, off_t offset, int bytes, char *buf,int opcode){
        aio->aio_fildes = fd;
        aio->aio_offset = offset;
        aio->aio_nbytes = bytes;
        aio->aio_buf = buf;
	/* This field could be LIO_READ for read request or LIO_WRITE for write
 	* request
        */
        aio->aio_lio_opcode = opcode;
}

int main(){
	
	struct aiocb a_write, a_read;
	struct aiocb *cblist[MAX];
	int err_r, err_w;
	int read_n = 0;
	int read_fd,write_fd;
	char read_buf[BUFFER_SIZE];
	char write_buf[BUFFER_SIZE];
	
	/* Open Read.txt file for reading */
	read_fd = open("Read.txt", O_RDONLY);

	/* Open Write.txt file for writing */
	write_fd = open("Write.txt", O_CREAT | O_WRONLY, 0644);

	/* Its good practice to clear the aiocbs before 
	 * using them
	 */
	memset(&a_write, 0 , sizeof(struct aiocb));
	memset(&a_read, 0 , sizeof(struct aiocb));


	/* populate aiocbs to defaults */
	populate_aiocb(&a_read, read_fd, 0, BUFFER_SIZE-1, read_buf,LIO_READ);
	populate_aiocb(&a_write, write_fd, 0, BUFFER_SIZE-1, write_buf,LIO_WRITE);

	/* Start async read. The function will read a_read.aio_nbytes bytes
	 * from file a_read.aio_fildes starting from a_read.aio_offset into 
	 * buffer a_read.aio_buf. On success 0 is returned. This function will
	 * return immediately after queueing the request
	 */
	cblist[0] = &a_read;
        cblist[1] = &a_write;

	while(1)
	{
		//aio_read(&a_read);
		lio_listio(LIO_NOWAIT, cblist, 2, NULL);
	
		/* After starting any async operation (read or write), you can get its status
		 * using aio_error function. This function returns EINPROGRESS if the request has not been completed
		 * It  returns ECANCELED if the request was cancelled.It returns 0
        	 * if the request completed successfully.  Otherwise  an  error  value  is returned
		 */
		if((err_r = aio_error(&a_read)) == EINPROGRESS || (err_w = aio_error(&a_write)) == EINPROGRESS){
                        cblist[0] = &a_read;
                        cblist[1] = &a_write;
                        aio_suspend(cblist, 2, NULL);
                }
		/* aio_error returns 0 that is success. Call aio_return to find of number of 
		 * bytes read. The function should be called only once after aio_error returns
		 * something other than EINPROGRESS.
		 */
		read_n  = aio_return(&a_read);
					
		strcpy(write_buf,read_buf);
		/* Setup write control block. Call aio_write to queue write request. The function 
		 * will write a_write.aio_nbytes bytes from buffer a_write.aio_buf to file a_write.aio_fildes
		 * at offset a_write.aio_offset. Returns 0 on success
		 */
		a_write.aio_nbytes = read_n;
		aio_write(&a_write);
		
		if(read_n!=BUFFER_SIZE-1)
			break;
		else
		{
			/* update read & write offset */
			a_read.aio_offset += read_n;
			a_write.aio_offset += aio_return(&a_write);
		}
	}
	close(read_fd);
	close(write_fd);

}
