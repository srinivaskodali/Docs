/* This file is a part of sniffer, a packet capture utility and
   Network Monitor
   Author : Team-V
   Version: 1.0
*/

#include<netinet/if_ether.h>
#include<stdio.h>
#include<netinet/in.h>	
#include<netinet/ether.h>
#include<stdlib.h>
#include<strings.h>
void Handle_ARP(char *buf)
{
	struct ether_arp *arp_hdr; // declared pointer of type arp header 
	struct in_addr in;
	char *hadd;

	FILE *fp;
	
	/* In the following statement we're adjusting the offset so
	   arp header pointer points to currect location */
	
	arp_hdr=(struct ether_arp *) (buf+14);
	
	fp=fopen("./output/arp.txt","a");

	if(!fp)
	{
		perror("fopen");
		exit(1);
	};
	fprintf(fp,"\t --------------------------------\n");
	system("date>> ./output/arp.txt");
	fprintf(fp,"hardware type : %u\n",ntohs(arp_hdr->ea_hdr.ar_hrd));
	fprintf(fp,"protocol type : %u\n",ntohs(arp_hdr->ea_hdr.ar_pro));
	fprintf(fp,"hardware length : %d\n",arp_hdr->ea_hdr.ar_hln);
	fprintf(fp,"protocol length : %d\n",arp_hdr->ea_hdr.ar_pln);
	fprintf(fp,"operation code  : %u\n",ntohs(arp_hdr->ea_hdr.ar_op));
	hadd=ether_ntoa((struct ether_addr *)arp_hdr->arp_sha);
	fprintf(fp,"sender hardware address : %s\n",hadd);
        bcopy(arp_hdr->arp_spa,&in.s_addr,4);   
	fprintf(fp,"sender protocol address : %s\n",inet_ntoa(in));
	bcopy(arp_hdr->arp_tpa,&in.s_addr,4);
	fprintf(fp,"target protocol address : %s\n",inet_ntoa(in));
	fprintf(fp,"\t ---------------------------------\n");

	fclose(fp);
}
	
	
