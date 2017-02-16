
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
	int sockfd,ret_val;
	struct sockaddr_in servaddr;
	char *msg;
	short *s,size;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9000);
	inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);

	ret_val = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(ret_val <0 ){
		perror("connect:");
		exit(1);
	}
// according to step (2)
	s = (short *) readNBytes(sockfd,2);
	msg = readNBytes(sockfd,*s);
	for(n=0;n<*s;n++)
		printf("%c",*(msg+n));
	printf("\n");
	scanf("%s",buf);
	size = strlen(buf);
// according to step (3)
	write(sockfd,&size,2);
	write(sockfd,buf,size);
// according to step (4)
	s = (short *) readNBytes(sockfd,2);
	msg = readNBytes(sockfd,*s);
	for(n=0;n<*s;n++)
		printf("%c",*(msg+n));
	printf("\n");
	close(sockfd);
}
