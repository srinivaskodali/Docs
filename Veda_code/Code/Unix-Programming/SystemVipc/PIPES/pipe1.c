/* shows how pipes can be used 
Version : 1.0
Author : Team -C
*/

# include <unistd.h>

main(){
	int fds[2];
	int res,i;
	char *buf1="aaaaaaaaaaaaaaaaaaaa";
	char *buf="bbbbbbbbbbbbbbbbbbbb";
	char buf2[10];
	res = pipe(fds); 
	/* fds[0] for reading and fds[1] for writing */
	if( res == -1 ){
		perror("pipe");
		exit(1);
	}
	write(fds[1],buf1,20);
	write(fds[1],buf,20);
	read(fds[0],buf2,10);
	for(i=0;i<10;i++)	
		printf("%c",buf2[i]);
	printf("\n");
}
		

