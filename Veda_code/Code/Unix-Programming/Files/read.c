/* To demonstrate read sysytem call 
Team : IDST
Version : 1.0
*/


#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main()
{
	char buf[30];
	int fd;

	
	if( (fd = open("read.txt", O_RDWR | O_CREAT | O_EXCL)) < 0)
	{	
		printf("\n open to fail");
		exit(0);
	}
	else
		printf("\n Open sucessfully");
	
	
	if( write(fd,"IDST",4) != 4)
	{
		printf("\n write error");
		exit(0);
	}
	//offset now = 4

	if( lseek(fd,0,0) == -1)
	{
		printf("\n lseek error");
		exit(0);
	}
	
	if( read(fd,buf,4) < 0)
	{
		printf("\n read error");
		exit(0);
	}
	printf("\n The read  msg : %s", buf);
	close(fd);

}
