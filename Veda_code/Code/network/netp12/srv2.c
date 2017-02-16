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


void urg_hand(int signo){
	printf(" signal handler called  indicating OOB\n");
}

/* following function will be handling the client in child process */

void handleClient(int connfd){
	fd_set read_set,excpt_set;
	int n,i;
	char buf[200];
	FD_ZERO(&read_set);
	FD_ZERO(&excpt_set);
	signal(SIGURG,urg_hand);
	while(1){
		FD_SET(connfd,&read_set);
		FD_SET(connfd,&excpt_set);
		n=select(100,&read_set,NULL,&excpt_set,NULL);	
		if(n <0)
			exit(1);
		if(FD_ISSET(connfd,&excpt_set)){
			n = recv(connfd,buf,100,MSG_OOB);
			printf("OOB DATA recd\n");
		}	
		if(FD_ISSET(connfd,&read_set)){
			n = read(connfd,buf,100);
			if(n == 0)
				exit(0);
			printf("normal data recd\n");
		}
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
