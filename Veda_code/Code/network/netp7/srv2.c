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
# include <stdio.h>
# include <stdlib.h>
main(){
int sockfd,retval,n,i,hlen;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;
char buf[1000];
char *app_data;
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
	myp_hdr = (struct myphdr *) (buf + 20);// first 20 bytes = ip hdr.
	printf("source app = %d\n",myp_hdr->source_app);
	printf("dest app = %d\n",myp_hdr->dest_app);
	printf("length of actual data = %d\n",myp_hdr->data_len);
	app_data = buf + 20 + sizeof(struct myphdr);
	for(i=0;i<myp_hdr->data_len;i++)
		printf("%c",*app_data++);
	printf("\n");
}
}
