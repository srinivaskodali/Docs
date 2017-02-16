/* shows how to analyze an application protocol using tcp. 
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
# include <netinet/tcp.h>
# include <stdio.h>
#include<stdlib.h>

main(){
	int pack_socket,n;
	FILE *fp;
	int len,datasize;
	char src_addr[20],dst_addr[20],*data;
	struct sockaddr_ll sa;	
	socklen_t sl;
	struct iphdr *ip_hdr;
	struct tcphdr *tcp_hdr;
	char buf[2000];
	fp = fopen("./tcpan1.dat","w");
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
		//check whether the packet is ip or not.
		if(ntohs(sa.sll_protocol) == 0x0800){
			printf(" IP packet received \t");
			ip_hdr = (struct iphdr *) buf;
			len = ip_hdr->ihl << 2;
			printf("ttl in ip hdr = %d\n",ip_hdr->ttl);
// if transport protocol is tcp
			if(ip_hdr->protocol == 6){
				tcp_hdr = (struct tcphdr *) (buf + len);
				//sing tcphdr we can get the details like src,dst ports
				fprintf(fp,"Details of TCP Packet \n");
				fprintf(fp,"source prt = %d\n",ntohs(tcp_hdr->source)); 
				fprintf(fp,"dest prt = %d\n",ntohs(tcp_hdr->dest)); 
				fprintf(fp,"seq = %d\n",ntohl(tcp_hdr->seq)); 
				fprintf(fp,"ack = %d\n",ntohl(tcp_hdr->ack_seq)); 
				fprintf(fp,"value of syn flag = %d\n",tcp_hdr->syn);
				fprintf(fp,"value of ack flag = %d\n",tcp_hdr->ack);
				fprintf(fp,"value of fin flag = %d\n",tcp_hdr->fin);
				fprintf(fp,"--------------------------------------------------------------\n");
				fflush(fp);
			}
		}
	}
	close(pack_socket);
}
