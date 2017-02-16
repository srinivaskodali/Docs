/* This file is part of sniffer, a packet capturing utility and
   Network Monitor
   Author : Team-V
   Version: 1.0
*/

#include<netinet/ip_icmp.h>
#include<stdio.h>
#include<stdlib.h>
void Handle_ICMP(char *buf,int len)
{
	struct icmphdr *icmp_hdr; // declaring pointer of type icmp header

	FILE *fp;

	fp=fopen("./output/icmp.txt","a");

	if(!fp)
	{
		perror("icmp.fopen");
		exit(1);
	}

	/* The following header is used to adjust offset so that icmp header
           can point to currect location */

	icmp_hdr=(struct icmphdr *) (buf+len);
	fprintf(fp,"\t --------------------------------\n");
	system("date>> ./output/icmp.txt");
	fprintf(fp,"message type : %d\n",icmp_hdr->type);
	fprintf(fp,"sub-code : %d\n",icmp_hdr->code);
	fprintf(fp,"\t --------------------------------\n");

	fclose(fp);
}
