/* kernel module to add netfilter call back */
#ifndef __KERNEL__
#define __KERNEL__
#endif
#ifndef MODULE
#define MODULE
#endif

#include <linux/ip.h>			/* IP Header*/
#include <linux/kernel.h>		/* Kernel */
#include <linux/module.h>		/* Module */
#include <linux/netdevice.h>		/* Interfaces */
#include <linux/netfilter.h>		/* Netfilter */
#include <linux/netfilter_ipv4.h>	/* Netfiletr for IPv4 */
#include <linux/skbuff.h>		/* Socket Kernel Buffers */
#include <linux/tcp.h>			/* TCP Header */

static struct nf_hook_ops netfilter_ops; 			/* Netfilter Options struct */
static unsigned char *ip_address = "192.168.0.1";  	
static char *interface = "lo"; 					/* Loopback Interface */
unsigned char *port = "23";					/* Port 23 (Telnet) */
struct sk_buff *sock_buff;					/* Socket Kernel Buffer */
struct tcphdr *tcp_header;					/* TCP Header */
#define NF_IP_PRE_ROUTING 0
unsigned int main_hook(unsigned int hooknum,
		  struct sk_buff **skb,
		  const struct net_device *in,
		  const struct net_device *out,
		  int (*okfn)(struct sk_buff*))
{

	if(strcmp(in->name,interface) == 0)
	{
		 return NF_DROP; 
	}	/* Drop Packet if on Loopback Interface */	

	sock_buff = *skb;
	
	if(!sock_buff){
	 	return NF_ACCEPT;
	 }/* Check for sk_buff NULL */

//	if(!(sock_buff->nh.iph)){
//		 return NF_ACCEPT;
//	}/* Check for valid IP Packet */

	/* Drop Packet if IP address == 192.168.0.1 */ 	
//	if(sock_buff->/*nh.iph->*/saddr == *(unsigned int*)ip_address)
//	{
//		 return NF_DROP;
//	}
		
	if(sock_buff->protocol != 6)
	{ 
		return NF_ACCEPT;
	}  /* Check for TCP Packet (6 == IPPROTO_TCP) */
	
	tcp_header = (struct tcphdr *)(sock_buff->data /*+ (sock_buff->nh.iph->ihl *4)*/);	/* Cast TCP Header */

	if((tcp_header->dest) == *(unsigned short*)port)
	{ 
		return NF_DROP;
        }  /* Drop if port == 23(telnet) */

return NF_ACCEPT;/* If all else fails, accept the Packet */
}

int init_module()
{
	netfilter_ops.hook		=	(nf_hookfn *) main_hook;
	netfilter_ops.hooknum		=	NF_IP_PRE_ROUTING;
	netfilter_ops.pf		=	PF_INET;
	netfilter_ops.priority		=	NF_IP_PRI_FIRST;

	nf_register_hook(&netfilter_ops);
	
return 0;
}

void cleanup_module()
{
	 nf_unregister_hook(&netfilter_ops);
}  /* Unregister Hook */

MODULE_LICENSE("GPL");

