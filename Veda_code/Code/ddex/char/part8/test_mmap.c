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
#include <string.h>
#define MAX_LENGTH 4096
main(){
	int fd,i;
	char *data= NULL,*temp;
	char *temp_buf;
	fd = open("/dev/veda_cdrv",O_RDONLY);
	getchar();
	data = (char *) mmap(0,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);	
	perror("\n MMAP STATUS: ");
	getchar();
	temp_buf = data;
	write(1,data,4096);
	memset(temp_buf,'v',MAX_LENGTH);
	msync(temp_buf,MAX_LENGTH,MS_SYNC);
	write(1,data,4096);
	munmap(data,4096);
}
