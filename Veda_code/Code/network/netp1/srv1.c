/* Example showing how to implement tcp/ip server.
Version: 1.0
Author : Team -C
*/
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
#include <netinet/in.h>

main(){
int listfd,connfd,retval;
//pid_t childpid;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;

listfd = socket(AF_INET, SOCK_STREAM, 0);
if (listfd < 0){
	perror("sock:");
	exit(1);
}
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);// any configured ip
servaddr.sin_port = htons(9000);//port no 8000

retval = bind(listfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
if(retval < 0){
	perror("bind:");
	exit(2);
}

listen(listfd, 5);

while(1){
	clilen = sizeof(cliaddr);
	connfd = accept(listfd, (struct sockaddr *) &cliaddr, &clilen);
	printf(" client connected \n");
	printf(" client's port no = %d\n",ntohs(cliaddr.sin_port));
	}
}
