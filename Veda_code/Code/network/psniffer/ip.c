/* This file is a part of a sniffer, a packet capture utility 
   and Network monitor
   Author : Team-V
   Version: 1.0
*/
	
#include<netinet/ip.h>
#include<stdio.h>
#include<stdlib.h>
#define ICMP 1
#define IGMP 2
#define TCP 6
#define UDP 17	

void Handle_ICMP(char *,int);
void Handle_IGMP(char *,int);
void Handle_TCP(char *,int);
void Handle_UDP(char *,int);

void Handle_IP(char *buf)
{
	struct iphdr *ip_hdr; // declaring pointer of type ip header 

	struct in_addr in; // declaring a structure which holds ip address 

	FILE *fp;
	int ctl,len;

	/* In the following statement we're adjusting the offset so that
	   ip pointer can point to currect location */

	ip_hdr=(struct iphdr * )(buf+14);

	fp=fopen("./output/ip.txt","a");

	if(!fp)
	{
		perror("fopen");
		exit(1);
	}
	
	fprintf(fp,"\t -------------------------------\n");
	system("date>> ./output/ip.txt");
	fprintf(fp,"type of service : %d\n",ip_hdr->tos);
	fprintf(fp,"protocol id is %d\n",ip_hdr->protocol);
	fprintf(fp,"total len %d\n",ntohs(ip_hdr->tot_len));
	fprintf(fp,"fragment offset %d\n",ntohs(ip_hdr->frag_off));
	
	/* In the following statement we're storing ip address in 
	   struct in_addr so that we can use inet_ntoa to convert
	   the same into ascii string  */	
	
	in.s_addr=ip_hdr->saddr;
	fprintf(fp,"source address is %s\n",inet_ntoa(in));

	in.s_addr=ip_hdr->daddr;
	fprintf(fp,"destination address is %s\n",inet_ntoa(in));
	fprintf(fp,"\t --------------------------------\n");

	ctl=ip_hdr->protocol;
	
	/* The following statement is used to calculate the combined
           length of data link header and ip header */
		
	len=(ip_hdr->ihl<<2)+14;

	/* The following switch statement can be used to invoke 
   	   appropriate handle function based on protocol id found
           in ip header */
		
	switch(ctl)
	{
	case ICMP:
		Handle_ICMP(buf,len);
		break;
	case IGMP:
		Handle_IGMP(buf,len);
		break;
	case TCP:
		Handle_TCP(buf,len);
		break;
	case UDP:
		Handle_UDP(buf,len);
		break;
	}

	fclose(fp);
}
		
