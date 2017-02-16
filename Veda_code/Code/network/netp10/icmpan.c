/* shows how to analyze an application protocol using udp. 
Author : Team -C.
Version: 1.0
Note: run the example along with ft and check the o/p.
*/
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netpacket/packet.h>
# include <net/ethernet.h>
# include <netinet/ip_icmp.h>
# include <stdio.h>
# include <stdlib.h>
main(){
	int pack_socket,n;
	int ip_len,udp_len,datasize,i;
	char src_addr[20],dst_addr[20],*data;
	struct sockaddr_ll sa;	
	socklen_t sl;
	struct iphdr *ip_hdr;
	struct icmphdr *icmp_hdr;
	char buf[2000];
	FILE *fp;
// sock_raw keeps physical layer header , sock_dgram removes it.
	fp = fopen("./icmpan.dat","w");
	pack_socket = socket(PF_PACKET,SOCK_DGRAM,htons(ETH_P_ALL));	
	if(pack_socket < 0){
		printf(" Failed to open packet socket\n");
		exit(0);
	}
	printf(" Packet Socket successfully opened\n");
	while(1){
		sl = sizeof(struct sockaddr_ll);
		n = recvfrom(pack_socket,buf,2000,0,(struct sockaddr *)&sa,&sl);
		//check whether the packet is ip or not.
		if(ntohs(sa.sll_protocol) == 0x0800){
			printf(" IP packet received \n");
			ip_hdr = (struct iphdr *) buf;
			ip_len = ip_hdr->ihl << 2;
// if transport protocol is icmp 
			if(ip_hdr->protocol == 1){
			icmp_hdr = (struct icmphdr *) (buf + ip_len);
			fprintf(fp,"Details of icmp message \n");
			switch(icmp_hdr->type){
				case ICMP_ECHO:
					fprintf(fp,"echo request\n");
					break;
				case ICMP_ECHOREPLY:
					fprintf(fp,"echo reply\n");
					break;
				case ICMP_DEST_UNREACH:
					fprintf(fp,"dest unreachable\n");
					break;
			}
			fprintf(fp,"\n--------------------------\n");
			fflush(fp);	
			}
		}
	}
	close(pack_socket);
}
