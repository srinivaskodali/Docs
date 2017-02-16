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
	int ip_len,tcp_len,datasize,i;
	char src_addr[20],dst_addr[20],*data;
	struct sockaddr_ll sa;	
	socklen_t sl;
	struct iphdr *ip_hdr;
	struct tcphdr *tcp_hdr;
	char buf[2000];
	fp = fopen("./tcpan2.dat","w");
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
			printf(" IP packet received \n");
			ip_hdr = (struct iphdr *) buf;
			ip_len = ip_hdr->ihl << 2;
// if transport protocol is tcp
			if(ip_hdr->protocol == 6){
			tcp_hdr = (struct tcphdr *) (buf + ip_len);
			tcp_len = tcp_hdr->doff <<2;
			fprintf(fp,"Details of TCP Packet \n");
			fprintf(fp,"source prt = %d\n",ntohs(tcp_hdr->source)); 
			fprintf(fp,"dest prt = %d\n",ntohs(tcp_hdr->dest)); 
			datasize = n - (ip_len + tcp_len);
			data = (char *) (buf + (ip_len + tcp_len));
			for(i=0;i<datasize;i++,data++)
				fputc(*data,fp);
			fprintf(fp,"\n---------------------------\n");
			fflush(fp);
			}
		}
	}
	close(pack_socket);
}
