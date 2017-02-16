/* To get the details of the hosts .
Version: 1.0
Author: Team -C
*/

# include <netdb.h>
# include <stdio.h>
# include <netinet/in.h>

main(){
	struct hostent *he = NULL;
	char dotaddr[20];
	he = gethostbyname("abc.com");
	if(he !=NULL){
		inet_ntop(AF_INET,he->h_addr,dotaddr,20);
		printf("address in dd notation = %s\n",dotaddr);
	}
	else
		printf("Unknown host\n");
}
