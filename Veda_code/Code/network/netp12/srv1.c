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
int sockfd;

void urg_hand(int signo){
	int n;
	char buf[10];
	printf(" signal handler called  indicating OOB\n");
	n = recv(sockfd,buf,10,MSG_OOB);
	printf(" received %d OOB data \n",n);
	printf(" data received = %c \n",buf[0]);
}

/* following function will be handling the client in child process */

void handleClient(int connfd){
	int n,i;
	char buf[200];
	signal(SIGURG,urg_hand);
	fcntl(connfd,F_SETOWN,getpid());// make this process as owner of sock.
	sockfd = connfd;
	for(i=0;i<3;i++){
		n = read(connfd,buf,200);
		buf[n]='\0';
		printf(" data rec'd from client = %s\n",buf);
	}
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
