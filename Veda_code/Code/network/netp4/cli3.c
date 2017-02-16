
/* Example showing how to implement udp/ip client.
Version: 1.0
Author : Team -C
*/
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
#include <netinet/in.h>
# include <stdio.h>
# include<stdlib.h>

main()
{
char *serv_ip = "127.0.0.1";
char msg[1000];
int sockfd,ret_val;
socklen_t addr_len;
char buf[1000];
struct sockaddr_in servaddr;
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if(sockfd <0 ){
	perror("error:");
	exit(1);
}
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(8000);
inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);
addr_len = sizeof(struct sockaddr_in);
//send data to the server socket, need not connect to server socket.
while(1){
scanf("%s",msg);
ret_val = sendto(sockfd,msg,strlen(msg),0,(struct sockaddr *)&servaddr,addr_len);
ret_val = recvfrom(sockfd,buf,1000,0,NULL,&addr_len); 
buf[ret_val]='\0';
printf("From server %s\n",buf);
}
close(sockfd);
}
