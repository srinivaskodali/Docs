/* shows how pipes can be used by parent and child to communicate with each other 
Version : 1.0
Author : Team -C
*/

# include <unistd.h>
# include <sys/types.h>


int fds[2];

/* let us assume that parent (process 1) will be writting to pipe and
child (process 2) will be reading from the pipe */

void parent_code(){
	char *buf1="aaaaaaaaaaaaaaaaaaaa";
	char *buf="bbbbbbbbbbbbbbbbbbbb";
	close(fds[0]);
	write(fds[1],buf,20);
	write(fds[1],buf1,20);
	printf(" end of parent\n");
}

void child_code(){
	char buf[100];
	int n,i;
	close(fds[1]);
	n = read(fds[0],buf,100);
	printf(" no of chars read = %d\n",n);
	for(i=0;i<n;i++)
		printf("%c",buf[i]);
	printf(" end of child \n");
}
main(){
	int res,i;
	pid_t p;
	res = pipe(fds); 
	/* fds[0] for reading and fds[1] for writing */
	if( res == -1 ){
		perror("pipe");
		exit(1);
	}
	p = fork();
	if(p == 0){
		child_code();
	}
	else{
		parent_code();
	}		
}
		

