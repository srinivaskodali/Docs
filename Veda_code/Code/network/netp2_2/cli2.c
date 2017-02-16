
/* Example showing how to implement tcp/ip client.
Version: 1.0
Author : Team -C
*/
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
#include <netinet/in.h>
#include<stdio.h>
#include<stdlib.h>

main()
{
char c;
char *serv_ip = "127.0.0.1";
int n;
int sockfd,ret_val;
struct sockaddr_in servaddr;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(8000);
inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);

ret_val = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
if(ret_val <0 ){
	perror("connect:");
	exit(1);
}
do{
	c = getchar();
	write(sockfd,&c,1);
}while(c != 'X');
printf(" closing connection with the server \n");
close(sockfd);
}
