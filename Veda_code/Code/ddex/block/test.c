/*test prog
Author:Team-c
Version:1.0
*/
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

main(){
	int fd,i;
	char buf[20]={};
	fd=open("/dev/sbd0", O_RDWR);
	if(fd<=0){
		perror("TEST FD:   ");
		exit(1);
	}
	ioctl(fd,BLKGETSIZE,&i);
	printf("result of ioctl %d\n",i);
	write(fd,"Mohan reddy",20);
	read(fd,buf,20);
	printf("\nDATA :%s",buf);
}
