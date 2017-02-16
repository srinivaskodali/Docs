
/* Example showing how to implement a protocol as part of client
Version: 1.0
Author : Team -C
*/

#include  "lib1.h"
#include  <stdio.h>
#include  <stdlib.h>
	

main(){
	char buf[200];
	char *serv_ip = "127.0.0.1";
	int n;
	socklen_t addr_len;
	int sockfd,ret_val,connfd;
	struct sockaddr_in servaddr;
	char *msg;
	short *s,size;

	sockfd = socket(AF_INET,SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9000);
	inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);

	addr_len = sizeof(struct sockaddr_in);

// according to step (2)
	s = (short *) readNBytes(sockfd,2);
	msg = readNBytes(sockfd,*s);
	for(n=0;n<*s;n++)
		printf("%c",*(msg+n));
	printf("\n");
	scanf("%s",buf);
	size = strlen(buf);
// according to step (3)
	//write(sockfd,&size,2);
	sendto(connfd,&size,2,0,(struct sockaddr *)&servaddr,addr_len);
	write(sockfd,buf,size);
	sendto(connfd,buf,size,0,(struct sockaddr *)&servaddr,addr_len);
	
// according to step (4)
	s = (short *) readNBytes(sockfd,2);
	msg = readNBytes(sockfd,*s);
	for(n=0;n<*s;n++)
		printf("%c",*(msg+n));
	printf("\n");
	close(sockfd);
}
