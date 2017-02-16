/* Shows how to use mmap sys call
Version : 1.0
Author : Team -C
*/

# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdio.h>

main(){
	int fd,i;
	unsigned char *filedata= NULL,*temp;
	fd = open("./test.file",O_RDWR);
	filedata = (char *) mmap((void*)0,125,PROT_READ|PROT_WRITE,\
			MAP_SHARED,fd,0);	
	if(filedata == NULL){
		perror("Maping Failed");
		exit(1);
	}
	temp = filedata;
	// now we can access the content of the file as if it is part of
	// our process starting from the memory pointed by filedata.
	for(i=0;i<125;i++,filedata++)
		*filedata = 'A';
	filedata = temp;
	for(i=0;i<125;i++,filedata++)
		putchar(*filedata);
	i=msync(temp,125,MS_SYNC);// wait till data is updated to disk.
	if( i == 0)
		printf(" file is successfully updated \n");	
	
	printf(" page size = %d\n",getpagesize());
}
