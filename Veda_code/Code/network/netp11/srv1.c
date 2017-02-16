/* Example showing how to implement tcp/ip server.
Version: 1.0
Author : Team -C
*/
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
#include <netinet/in.h>
# include <sys/time.h>
#include<stdio.h>
#include<stdlib.h>


/* following function will be handling the client in child process */

void handleClient(int connfd){
	int n;
	socklen_t size;
	struct linger lin;
	struct timeval rt;
	char buf[200];
	size = sizeof(int);
	getsockopt(connfd,SOL_SOCKET,SO_RCVBUF,(void *)&n,&size);
	printf("size of recv buf = %d\n",n);
	getsockopt(connfd,SOL_SOCKET,SO_SNDBUF,(void *)&n,&size);
	printf("size of send buf = %d\n",n);
	printf("Trying to send recv buf size\n");
	n=50;
	setsockopt(connfd,SOL_SOCKET,SO_RCVBUF,(void *)&n,size);
	getsockopt(connfd,SOL_SOCKET,SO_RCVBUF,(void *)&n,&size);
/* when close is executed on a socket the call returns immediately but the 
system tries to send the data in the send buffer */
	lin.l_onoff = 1 ; /* 0 for default action on close */
	lin.l_linger = 3 ; /* linger on for 3 seconds */
	size = sizeof(struct linger);
	setsockopt(connfd,SOL_SOCKET,SO_LINGER,(void *)&lin,size);
	rt.tv_sec=1;
	rt.tv_usec = 0; //microsec.
	size = sizeof(struct timeval);
	setsockopt(connfd,SOL_SOCKET,SO_RCVTIMEO,(void *)&rt,size);
/* wait for three seconds if the data is in the send buffer before returning
from close call */
	printf("size of recv buf = %d\n",n);
	n = read(connfd,buf,200);
	printf(" return values of read = %d\n",n);
	buf[n]='\0';
	printf(" data rec'd from client = %s\n",buf);
	printf(" requested handled by server %d\n",getpid());
	write(connfd,"Good Bye",8);
	close(connfd);
	exit(0); // terminate child.
}

main(){
int listfd,connfd,retval;
pid_t childpid;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;

listfd = socket(AF_INET, SOCK_STREAM, 0);
if (listfd < 0){
	perror("sock:");
	exit(1);
}
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(8000);

retval = bind(listfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
if(retval < 0){
	perror("bind:");
	exit(2);
}

listen(listfd, 5);

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
