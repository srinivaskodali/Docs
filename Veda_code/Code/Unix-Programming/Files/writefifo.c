
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
	int fd;
	fd = open("./myfifo",O_WRONLY);
	if(fd < 0){
		perror("Pipe Error :");
		exit(1);
	}
	write(fd,"abc",3);
	write(fd,"abc",3);
	write(fd,"abc",3);
}
