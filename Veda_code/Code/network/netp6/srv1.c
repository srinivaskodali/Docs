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
#include <stdio.h>
#include<stdlib.h>

main(){
int sockfd,retval,n,i,hlen;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;
char buf[10000]; 
char addr[20];
struct iphdr *ip_hdr;
printf("ICMP Protocol NO =%d\n",IPPROTO_ICMP);	
sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
if (sockfd < 0){
	perror("sock:");
	exit(1);
}
printf(" raw socket created\n");
clilen = sizeof(struct sockaddr_in);
while(1){
	printf(" before recvfrom\n"); 	
	n=recvfrom(sockfd,buf,10000,0,(struct sockaddr *)&cliaddr,&clilen);
	printf(" received %d bytes \n",n); 
	ip_hdr = (struct iphdr *) buf;
	printf("Here are the details available in ip header \n");
	hlen = ip_hdr->ihl<<2;
	printf(" Length of ip header = %d\n",hlen);
	printf(" tot_len = %d\n",ntohs(ip_hdr->tot_len));
	printf("protocol = %d\n",ip_hdr->protocol);
	inet_ntop(AF_INET,&(ip_hdr->saddr),addr,20);
	printf("Source address = %s\n",addr);
	inet_ntop(AF_INET,&(ip_hdr->daddr),addr,20);
	printf("Destination address = %s\n",addr);
	printf("\n");
}
}
