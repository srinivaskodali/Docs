/* This file is a part of sniffer, a packet capture utility and
   Network monitor.
   Author : Team-V
   Version: 1.0
*/

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netpacket/packet.h>
#include<netinet/if_ether.h>
#include<stdio.h>
#include<stdlib.h>
void Handle_IP(char *);
void Handle_ARP(char *);	
void Handle_RARP(char *);

int main()
{
	struct sockaddr_ll sa; // declaring a structure which hold link
                               // level header information */

	struct ethhdr *eth_hdr; // pointer for ethernet header 

	int sockfd,sl,retval,ctl;

	char buf[2000],*hadd;
	
	FILE *fp;

	/* The following system call creates raw socket which captures
	   all protocols */
	
	sockfd=socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));

	if(sockfd<0)
	{
		perror("socket");
		exit(1);
	}
	fp=fopen("./output/ether.txt","a");
	if(!fp)
	{
		perror("fopen");
		exit(1);
	}
	setvbuf(fp,NULL,_IONBF,0);

	/* The following infinite while loop is used to continuously
	   capture packets and afterwards the packet will be passed
	   to appropriate handler */	

	while(1)
	{
		sl=sizeof(struct sockaddr_ll);
		retval=recvfrom(sockfd,buf,2000,0,(struct sockaddr *)&sa,&sl);
		if(retval==-1)
		{
			perror("recvfrom");
			exit(1);
		}
		eth_hdr=(struct ethhdr *) buf;
		fprintf(fp,"\t ----------------------------\n");
		system("date>>./output/ether.txt");
		hadd=(char *)ether_ntoa((struct ether_addr *)eth_hdr->h_source);
		fprintf(fp,"source ethernet address is %s\n",hadd);
		hadd=(char *)ether_ntoa((struct ether_addr *)eth_hdr->h_dest);
		fprintf(fp,"destination ethernet address is %s\n",hadd);
		fprintf(fp,"packet protocol id is %x\n",ntohs(eth_hdr->h_proto));
		fprintf(fp,"\t ----------------------------\n");
		ctl=ntohs(eth_hdr->h_proto);
		switch(ctl)
		{
			case 0x0800:
				printf("received IP packet\n");
				Handle_IP(buf);	
				break;

			case 0x0806:
				printf("received ARP packet\n");
				Handle_ARP(buf);
				break;
			case 0x8035:
				printf("received RARP packet\n");
				Handle_RARP(buf);
				break; 
		}
				
	}

	fclose(fp);
	return 0;
}
		
		
	
	
