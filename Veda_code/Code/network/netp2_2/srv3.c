/* Example showing how to implement tcp/ip server.
Version: 1.0
Author : Team -C
Note : Write a function which reads till it receives the chars r followed by s.
*/
# include "lib1.h"
#include<stdlib.h>
/* following function will be handling the client in child process */

void handleClient(int connfd){
	int n,i;
	char *buf;
	buf = readNBytes(connfd,10);
	for(i=0;i<10;i++,buf++)
		printf("%c \n",*buf);
	exit(0); // terminate child.
}

main(){
int listfd,connfd,retval;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;
listfd = connandlisten(8000);
while(1){
	char buf[200];
	pid_t p;
	int n;
	clilen = sizeof(cliaddr);
	connfd = accept(listfd, (struct sockaddr *) &cliaddr, &clilen);
	printf(" client connected \n");
	p = fork();
	if( p == 0){
		close(listfd);
		handleClient(connfd);
	}
	close(connfd);
}
}
