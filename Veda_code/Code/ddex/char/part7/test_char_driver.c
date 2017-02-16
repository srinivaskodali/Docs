/* test_char_driver.c
** Team: Veda
** Version: 1.0
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <aio.h>
/**
* This program uses the device driver veda_chr_driver and opens a file on it.
* It performs the read, write and lseek operation apart from open() and close()
* Hence it checks the drivers functionality
*/


int main()
{
	int fd;
	char buf[20];
	struct aiocb *async_iocb;
	if((fd = open("/dev/veda_cdrv",O_RDONLY)) < 0)
	{
		perror("\n fd status: ");
		exit(0);	
	}
	async_iocb = (struct aiocb *)malloc(sizeof(struct aiocb));
	async_iocb->aio_fildes=fd;
	async_iocb->aio_buf=&buf;
	async_iocb->aio_nbytes=20;
	aio_read(async_iocb);
	sleep(1);
	write(1,buf,strlen(buf));
	printf("\nbuffer %s \n ",buf);
	close(fd);
}
