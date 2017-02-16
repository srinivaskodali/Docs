/* Shows how write works without using append flag.
Version : 1.0
Author : Team -C
*/

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>

main(){
	int fd;
	off_t offset;
	fd = open("./newfile",O_RDWR|O_CREAT|O_APPEND);
	if( fd < 0){
		perror("file :");
		exit(1);
	}
	printf(" ..\n");
	write(fd,"one",3);
	printf(" ..\n");
	offset = lseek(fd,0,SEEK_CUR);
	printf(" current file pointer is at %d\n",offset);
	write(fd,"two",3);
	write(fd,"thr",3);
	write(fd,"fou",3);
	offset = lseek(fd,0,SEEK_CUR);
	printf(" current file pointer is at %d\n",offset);
	offset = lseek(fd,-6,SEEK_CUR);
	printf(" current file pointer is at %d\n",offset);
	write(fd,"fiv",3);
}
