/* Example showing how to implement tcp/ip server.
Version: 1.0
Author : Team -C
*/
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
# include <netinet/in.h>
# include <signal.h>
# include <fcntl.h>
#include <stdio.h>
#include<stdlib.h>



/* following function will be handling the client in child process */

void handleClient(int connfd){
	int n,i;
	char buf[200];
	while(1){
		if(sockatmark(connfd))
			printf("OOB\n");
		n = read(connfd,buf,100);
		if(n ==0)
			exit(0);
		printf("recd %d bytes \n",n);
	}
}

main(){
int listfd,connfd,retval,n;
pid_t childpid;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;
listfd = socket(AF_INET, SOCK_STREAM, 0);
n=1 ; //1 for on , 0 for off
setsockopt(listfd,SOL_SOCKET,SO_OOBINLINE,&n,4);
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
