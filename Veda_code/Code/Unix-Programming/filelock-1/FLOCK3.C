# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/file.h>

main(){
	int fd,loc_res;
	fd = open("./file1",O_RDWR);
	loc_res=flock(fd,LOCK_EX|LOCK_NB);
	printf(" result of locking = %d\n",loc_res);
	getchar();
}
