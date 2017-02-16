/* To show holes in a file
Team : IDST
Version : 1.0
*/

#include <unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>

int main(void)
{
	int fd;
	if ( (fd = open("filewithhole",O_WRONLY|O_CREAT)) < 0){
		perror("File Open:");
		exit(0);
	}
	write(fd,"AAAAAAAAAA", 10);
	lseek(fd, 90, SEEK_SET);
	printf(" file pointer is at %d\n",lseek(fd,0,SEEK_CUR));
	write(fd,"ZZZZZZZZZZ",10);
	printf(" file pointer is at %d\n",lseek(fd,0,SEEK_CUR));
}
