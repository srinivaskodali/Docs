/* This file is a part of sniffer, a packet capture utility and
   Network Monitor
   Author : Team-V
   Version: 1.0
*/

#include<netinet/if_ether.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
void Handle_RARP(char *buf)
{
	struct ether_arp *rarp_hdr; // declaring a pointer of type arp header 
	struct in_addr in;
	char *hadd;

	FILE *fp;

	/* The following statement can be used to adjust offset so that
	    arp header points to currect location */

	rarp_hdr=(struct ether_arp *) (buf+14);

	fp=fopen("./output/rarp.txt","a");

	if(!fp)
	{
		perror("fopen");
		exit(1);
	};
	
	fprintf(fp,"\t -----------------------------------\n");
	system("date>> ./output/rarp.txt");
	fprintf(fp,"hardware type : %u\n",ntohs(rarp_hdr->ea_hdr.ar_hrd));
	fprintf(fp,"protocol type : %u\n",ntohs(rarp_hdr->ea_hdr.ar_pro));
	fprintf(fp,"hardware length : %d\n",rarp_hdr->ea_hdr.ar_hln);
	fprintf(fp,"protocol length : %d\n",rarp_hdr->ea_hdr.ar_pln);
	fprintf(fp,"operation code  : %u\n",ntohs(rarp_hdr->ea_hdr.ar_op));
	hadd=(char *)ether_ntoa((struct ether_addr *)rarp_hdr->arp_sha);
	fprintf(fp,"sender hardware address : %s\n",hadd);
	bcopy(rarp_hdr->arp_spa,&in.s_addr,4);
	fprintf(fp,"sender protocol address : %s\n",inet_ntoa(in));
	hadd=(char *)ether_ntoa((struct ether_addr *)rarp_hdr->arp_tha);
	fprintf(fp,"target harware address : %s\n",hadd);
	fprintf(fp,"\t ------------------------------------\n");

	fclose(fp);
}
	
	
