/* Shows how to use mmap sys call
Version : 1.0
Author : Team -C
Note : All modern OS supports memory mapping of files.
*/

# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdio.h>

main(){
	int fd,i;
	unsigned char *filedata= NULL,*temp;
	fd = open("/dev/veda_cdrv",O_RDONLY);
	filedata = (char *) mmap((void*)0,20,PROT_READ|PROT_WRITE,\
			MAP_PRIVATE,fd,0);	
	perror("\n MMAP STATUS: ");
	write(1,(char *)filedata,strlen((char *)filedata));
	
	if(filedata == NULL){
		perror("Maping Failed");
		exit(1);
	}
	// now we can access the content of the file as if it is part of
	// our process starting from the memory pointed by filedata.
	temp = filedata;
	write(1,filedata,strlen(filedata));
	//for(i=0;i<100;i++,filedata++)
	//	putchar(*filedata);
	i = munmap(temp,100);
	if( i != 0)
		printf(" failed to unmap\n");
}
