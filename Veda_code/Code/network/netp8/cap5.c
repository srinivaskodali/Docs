/* shows how to  find out  transport protocol details in ip header.
Author : Team -C.
Version: 1.0
Note: run the example along with ft and check the o/p.
*/
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netpacket/packet.h>
# include <net/ethernet.h>
# include <linux/ip.h>
#include<stdio.h>
#include<stdlib.h>

main(){
	int pack_socket,n;
	struct sockaddr_ll sa;	
	socklen_t sl;
	struct iphdr *ip_hdr;
	char buf[2000];
// sock_raw keeps physical layer header , sock_dgram removes it.
	pack_socket = socket(PF_PACKET,SOCK_DGRAM,htons(ETH_P_ALL));	
	if(pack_socket < 0){
		printf(" Failed to open packet socket\n");
		exit(0);
	}
	printf(" Packet Socket successfully opened\n");
	while(1){
		sl = sizeof(struct sockaddr_ll);
	n = recvfrom(pack_socket,buf,2000,0,(struct sockaddr *)&sa,&sl);
//for details on ip header refer to linux/ip.h.
		//check whether the packet is ip or not.
		if(ntohs(sa.sll_protocol) == 0x0800){
			printf(" IP packet received \n");
			ip_hdr = (struct iphdr *) buf;
			printf("Details of IP Packet \n");
		printf("Transport protocol  = %d\n",ip_hdr->protocol);
//1 icmp , 2 igmp, 6 tcp, 17 udp ..
		}
	}
	close(pack_socket);
}
