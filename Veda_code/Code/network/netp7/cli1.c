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
int sockfd,retval,n,i,len;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;
char *data = "APPLICATION DATA";
char *temp;
char buf[1000];
struct myphdr *myp_hdr;
myp_hdr = (struct myphdr *) buf;
myp_hdr->source_app = 100;
myp_hdr->dest_app = 200;
myp_hdr->data_len = strlen(data);
temp = buf + sizeof(struct myphdr);

servaddr.sin_family= AF_INET;
inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);

for(i=0;i<myp_hdr->data_len;i++)
	*temp++ = data[i];
	
len = sizeof(struct myphdr) + strlen(data);
sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_MYPROTO);
if (sockfd < 0){
	perror("sock:");
	exit(1);
}
printf(" raw socket created\n");
n=sendto(sockfd,buf,len,0,(struct sockaddr *) &servaddr,sizeof(struct sockaddr_in));
printf("sent %d bytes from client \n",n);
}
