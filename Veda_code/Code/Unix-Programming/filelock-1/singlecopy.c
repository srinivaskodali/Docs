# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/file.h>

# define FILENAME  "singlecopy.pid"

main(){
	int fd,loc_res;
	pid_t pid;
	pid = getpid();
	fd = open(FILENAME,O_RDWR|O_CREAT);
	loc_res=flock(fd,LOCK_EX|LOCK_NB);
	if(loc_res !=0){
		printf(" Another Copy is running \n");
		exit(0);
	}
	while(1){
		printf(" performing operations \n");
	}
	close(fd);
}
/* Note : check fcntl documentation for locking files in read/write mode */
