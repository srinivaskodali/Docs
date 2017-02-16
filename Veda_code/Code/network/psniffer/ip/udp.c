/* This file is part of sniffer, a packet capturing utility and
   Network Monitor
   Author : Team-V
   Version: 1.0
*/

#include<netinet/udp.h>
#include<stdio.h>
#include<stdlib.h>
void Handle_UDP(char *buf,int len)
{
	struct udphdr *udp_hdr; // declaring a pointer of type udp header

	FILE *fp;

	fp=fopen("./output/udp.txt","a");

	if(!fp)
	{
		perror("udp.fopen");
		exit(1);
	}
	
	/* The following statement is used to adjust the offset so that
	   udp header can point to currect location */

	udp_hdr=(struct udphdr*) (buf+len);
	fprintf(fp,"\t ----------------------------------\n");
	system("date>>./output/udp.txt");
	fprintf(fp,"source port no : %u\n",ntohs(udp_hdr->source));
	fprintf(fp,"destination port no : %u\n",ntohs(udp_hdr->dest));
	fprintf(fp,"header length : %u\n",ntohs(udp_hdr->len));
	fprintf(fp,"\t ----------------------------------\n");

	fclose(fp);
}
