/* This file is part of sniffer, a packet capturing utility and 
   Network Monitor
   Author : Team-V
   Version: 1.0
*/

#include<netinet/igmp.h>
#include<stdio.h>
#include<stdlib.h>
void Handle_IGMP(char *buf,int len)
{
	struct igmp *igmp_hdr; // declaring pointer of type igmp header

	struct in_addr in; // declaring a structure to store ip address

	FILE *fp;

	igmp_hdr=(struct igmp *) (buf+len);

	fp=fopen("./output/igmp.txt","a");

	if(!fp)
	{
		perror("igmp.fopen");
		exit(1);
	}

	fprintf(fp,"\t ---------------------------------\n");
	system("date>> ./output/igmp.txt");
	fprintf(fp,"igmp type : %d\n",igmp_hdr->igmp_type);

	/* Storing ip address in struct in_addr so that we can 
           execute inet_ntoa() to retreive the same in string
           format */

	in.s_addr=igmp_hdr->igmp_group.s_addr;

	fprintf(fp,"igmp group : %s\n",inet_ntoa(in));
	fprintf(fp,"\t ---------------------------------\n");

	fclose(fp);
} 
