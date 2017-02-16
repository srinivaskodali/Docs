
/* Shows how to use FIFO for passing data between two different
processes. 
Version: 1.0
Author : Team -C
*/

/* Note create a FIFO with name myfifo in current directory */

# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

main(){
	int fd,i;
	char buf[20];
	ssize_t size;
	fd = open("./myfifo",O_RDONLY);
	if(fd < 0){
		perror("Pipe Error :");
		exit(1);
	}
	size =  read(fd,buf,15);
	printf(" no of bytes read from FIFO = %d\n",size);
	for(i=0;i<size;i++)
		printf("%c\n",buf[i]);
}
