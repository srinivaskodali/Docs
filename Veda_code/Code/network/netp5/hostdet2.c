/* To get the details of the hosts .
Version: 1.0
Author: Team -C
*/

# include <netdb.h>
# include <stdio.h>
# include <netinet/in.h>

main(){
	struct hostent *he = NULL;
	char **aliases;
	int i;
	char dotaddr[20];
	he = gethostbyname("abc.com");
	if(he !=NULL){
		aliases = he->h_aliases;
		for(i=0;aliases[i]!=NULL;i++)
			printf("alias %d = %s\n",i,aliases[i]);
	}
	else
		printf("Unknown host\n");
}
