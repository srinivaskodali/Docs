/* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <asm/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define MAX_PAYLOAD 1024
#define NETLINK_MYLINK 18
struct sockaddr_nl s_addr, d_addr;
struct nlmsghdr *nlmh;
struct msghdr m_hdr;
struct iovec iov; 	//<bits/uio.h>
char Msg[MAX_PAYLOAD];
int socfd, i;

int main() {
/*create socket*/

socfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_MYLINK);
printf (" socfd is %d\n\n", socfd);

/* Filling the netlink address structure */

memset(&s_addr, 0, sizeof(s_addr));
s_addr.nl_family = AF_NETLINK;
s_addr.nl_pid = getpid();
s_addr.nl_groups = 0;

/* binding the address to socket*/

bind(socfd, (struct sockaddr*)&s_addr, sizeof(s_addr));

/* Filling the netlink addr structure -destn */

memset(&d_addr, 0, sizeof(d_addr));
d_addr.nl_family = AF_NETLINK;
d_addr.nl_pid = 0;
d_addr.nl_groups = 0;

nlmh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));

/*Fill the netlink message header */

nlmh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
nlmh->nlmsg_pid = getpid();
nlmh->nlmsg_flags = 0;

printf("Enter Msg to be sent\n");
fgets(Msg, MAX_PAYLOAD, stdin);

strcpy(NLMSG_DATA(nlmh), Msg);

iov.iov_base = (void *)nlmh;         /*starting addr.*/
iov.iov_len = nlmh->nlmsg_len;       /*No. of bytes*/
m_hdr.msg_name = (void *)&d_addr; 
m_hdr.msg_namelen = sizeof(d_addr);
m_hdr.msg_iov = &iov;
m_hdr.msg_iovlen = 1;

sendmsg(socfd, &m_hdr, 0);

/*Read message from kernel*/

memset(nlmh, 0,NLMSG_SPACE(MAX_PAYLOAD));
i = recvmsg(socfd, &m_hdr, 0);
printf("\n\nreceived msg :%s\n", NLMSG_DATA(nlmh));

close(socfd);

}










