
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

main(){
	int fd;
	unsigned char b;
	int no,i;
	fd = open("/dev/mykb",O_RDONLY);
	perror("mykb");
	printf(" fd = %d\n",fd);
	for(i=0;i<20;i++){
		no = read(fd,&b,1);
		printf("\ncode = %d\n ",b);
	}
	close(fd);
}
	
