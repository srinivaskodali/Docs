
/* change the size of the buffer to read a file
Version : 1.0
Author : Team -C
*/

# include <sys/types.h>
# include <sys/times.h>
# include <unistd.h>
# include <fcntl.h>

# define BUF_SIZE  2048

void display_time(void){
	struct tms t;
	times(&t);
	printf(" User Time = %d \n",t.tms_utime);
	printf(" System Time = %d \n",t.tms_stime);
}
main(){
	char buf[BUF_SIZE];
	ssize_t count;
	int fd;
	fd = open("/boot/boot.b",O_RDONLY);
	if( fd < 0 ){
		perror(" File Open:");
		exit(1);
	}
	do{
		count = read(fd,buf,BUF_SIZE);
	}while(count != 0);
	display_time();
}
	
	
