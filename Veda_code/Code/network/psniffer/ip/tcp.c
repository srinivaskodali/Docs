/* This file is a part of sniffer, a packet capturing utility and
   Network Monitor
   Author : Team-V
   Version: 1.0
*/

#include<netinet/tcp.h>
#include<stdio.h>
#include<stdlib.h>

void Handle_TCP(char *buf,int len)
{
	struct tcphdr *tcp_hdr; // declaring a pointer of type tcp header

	FILE *fp;

	fp=fopen("./output/tcp.txt","a");

	if(!fp)
	{
		perror("tcp.fopen");
		exit(1);
	}
	
	/* The following statement is used to adjust the offset so that
	   tcp header pointer can point to currect location */

	tcp_hdr=(struct tcphdr *) (buf+len);
	
	fprintf(fp,"\t ----------------------------------\n");
	system("date>> ./output/tcp.txt");
	fprintf(fp,"source port no : %u\n",ntohs(tcp_hdr->source));
	fprintf(fp,"destination port no : %u\n",ntohs(tcp_hdr->dest));
	fprintf(fp,"seq number : %lu\n",ntohl(tcp_hdr->seq));
	fprintf(fp,"ack number : %lu\n",ntohl(tcp_hdr->ack_seq));
	fprintf(fp,"window size : %u\n",ntohs(tcp_hdr->window));
	fprintf(fp,"\t ----------------------------------\n");

	fclose(fp);
}
	
	
