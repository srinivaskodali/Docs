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
# include <linux/ip.h>
# include <netinet/udp.h>
# include <stdio.h>
# include <stdlib.h>
main(){
	int pack_socket,n;
	int ip_len,udp_len,datasize,i;
	char src_addr[20],dst_addr[20],*data;
	struct sockaddr_ll sa;	
	socklen_t sl;
	struct iphdr *ip_hdr;
	struct udphdr *udp_hdr;
	char buf[2000];
	FILE *fp;
// sock_raw keeps physical layer header , sock_dgram removes it.
	fp = fopen("./udpan1.dat","w");
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
// if transport protocol is udp 
			if(ip_hdr->protocol == 17){
			udp_hdr = (struct udphdr *) (buf + ip_len);
			udp_len = sizeof(struct udphdr);
		// using tcphdr we can get the details like src,dst ports
			fprintf(fp,"Details of UDP Packet \n");
			data = (char *) (buf + ip_len + udp_len);
			datasize = n - (ip_len + udp_len);
			fprintf(fp,"source port = %d\n",ntohs(udp_hdr->source));
			fprintf(fp,"dest port = %d\n",ntohs(udp_hdr->dest));
			for(i=0;i<datasize;i++,data++)
				fputc(*data,fp);
			fprintf(fp,"\n---------------------\n");
			fflush(fp);	
			}
		}
	}
	close(pack_socket);
}
