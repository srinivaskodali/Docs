
#ifndef MODULE
	#define MODULE
#endif

#ifndef __KERNEL__
	#define __KERNEL__
#endif

#define NETLINK_MYLINK 18

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/socket.h>
#include <linux/skbuff.h>
#include <net/sock.h>
#include <linux/wait.h>
#include <linux/netlink.h>



MODULE_LICENSE("GPL");

void netlink_mylink(void);
void input(struct sock *sk, int len);

static int __init  my_init(void)
{
	printk("Module In\n");
	netlink_mylink();
	return 0;
}

static void __exit my_exit(void)
{
	printk("Module out\n");
}

module_init(my_init);
module_exit(my_exit);

struct sock *nl_skt = NULL;

void  input(struct sock *sk, int len)
{
	wake_up_interruptible(sk->sk_sleep);
}


void netlink_mylink()
 {
 struct netlink_skb_parms nl_skp;
 struct sk_buff *skb = NULL;
 struct nlmsghdr *nlmh = NULL;
 u32 pid;
 int err;
 nl_skt = netlink_kernel_create((struct net *)NETLINK_MYLINK,0,0,(void *)input,NULL,NULL);
 //nl_skt = netlink_kernel_create(NETLINK_MYLINK, input);

 /* Message from user-space */

 skb = skb_recv_datagram(nl_skt, 0, 0, &err);
 nlmh = (struct nlmsghdr *)skb->data;

 printk("Received netlink message payload:  %s\n",(char *)NLMSG_DATA(nlmh));
 pid = nlmh->nlmsg_pid; 

 strcpy(NLMSG_DATA(nlmh), "Greeting from kernel!");
/* Setting the local address */
 
 nl_skp.pid = 0;      

/* Setting the destn. address */
 nl_skp.pid = pid;
 nl_skp.dst_group = 0;  

 netlink_unicast(nl_skt, skb, pid, MSG_DONTWAIT);
 sock_release(nl_skt->sk_socket);

}

