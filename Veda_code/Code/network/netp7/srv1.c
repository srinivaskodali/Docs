/* Example showing how to implement udp/ip server.
Version: 1.0
Author : Team -C
*/
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
# include <netinet/in.h>
/* for struct iphdr */
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include "myproto.h"
# include <stdlib.h>
# include <stdio.h>
main(){
int sockfd,retval,n,i,hlen;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;
char buf[1000];
struct myphdr *myp_hdr;
sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_MYPROTO);
if (sockfd < 0){
	perror("sock:");
	exit(1);
}
printf(" raw socket created\n");
while(1){
	printf(" before recvfrom\n"); 	
	n=recvfrom(sockfd,buf,1000,0,(struct sockaddr *)&cliaddr,&clilen);
	printf(" received %d bytes \n",n); 
	myp_hdr = (struct myphdr *) buf;
}
}
