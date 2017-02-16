# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/file.h>

main(){
	int fd,n;
	char buf[10]={'a','a','a','a','a','a'};
	fd = open("./file1",O_RDWR);
	n=write(fd,buf,6);
	printf(" no of bytes written = %d\n",n);
	getchar();
}
