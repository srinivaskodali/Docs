/* Shows how to use Fork system call 
Version : 1.0
Author : Team -C
*/

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define CHILD 0

main(){
	int fd;
	char buf[2];
        pid_t pid;	
	int childstatus;
	pid = fork();
	if( pid == CHILD){
		read(fd,buf,2);
		perror("child:");
		printf(" in child %c\n",buf[0]);
		printf(" in child %c\n",buf[1]);
		close(fd);
	}
	// parent
	else{
		fd = open("./test",O_RDONLY);
		wait(&childstatus);
		read(fd,buf,2);
		printf(" in parent %c\n",buf[0]);
		printf(" in parent %c\n",buf[1]);
		close(fd);
	}
}
		

