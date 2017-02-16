/* To get the port no of a service.
Version: 1.0
Author: Team -C
*/

# include <netdb.h>
# include <stdio.h>

main(){
	struct servent *se=NULL;
	se = getservbyname("inetservice","tcp"); //servicename, protocol.
	printf(" se = %x\n", se);
	se = getservbyname("echo","tcp"); //servicename, protocol.
	printf(" se = %x\n", se);
	if( se !=NULL)
		printf(" port no of service = %d\n",ntohs(se->s_port));
	else
	printf(" no protocol entry found in /etc/services\n");
}
