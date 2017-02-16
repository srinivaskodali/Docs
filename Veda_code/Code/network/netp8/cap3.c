/* shows how to  find out the type of packet we captured.
Author : Team -C.
Version: 1.0
Note: run the example along with ft and check the o/p.
*/
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netpacket/packet.h>
# include <net/ethernet.h>
#include<stdio.h>
#include<stdlib.h>

main(){
	int pack_socket,n;
	struct sockaddr_ll sa;	
	socklen_t sl;
	char buf[2000];
// sock_raw keeps physical layer header , sock_dgram removes it.
	pack_socket = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));	
	if(pack_socket < 0){
		printf(" Failed to open packet socket\n");
		exit(0);
	}
	printf(" Packet Socket successfully opened\n");
	while(1){
		sl = sizeof(struct sockaddr_ll);
		n = recvfrom(pack_socket,buf,2000,0,(struct sockaddr *)&sa,&sl);
		printf(" Received packet of length %d\n", n);
		printf(" Packet type = %d\n",sa.sll_pkttype);
		printf(" Hardware address length = %d\n",sa.sll_halen);
		printf(" Protocol  = %x\n",ntohs(sa.sll_protocol));
	//refer to netpacket/packet.h file for pkttype values.
	// refer linux/if_ether.h for list of protocol types.
//0x800 is for ip , 0x806 for ARP etc.
	}
	close(pack_socket);
}
