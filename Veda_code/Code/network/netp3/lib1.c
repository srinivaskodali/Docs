/*  Helper Functions( lib1.c).
Version: 1.0
Author : Team -C
*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
#include <netinet/in.h>

/* this function reads exactly n bytes and places it in buffer before
returning, if it fails to read exactly n bytes then it will return NULL */

char * readNBytes(int connfd, int n){
	char *buf,*tbuf;
	int nobread=0,nr,ntor;
	ntor = n;
	buf = (char *) malloc(n);
	tbuf = buf;
	if( buf == NULL)
		return NULL;
	while(1){
		nr = read(connfd,tbuf,ntor);
		
		printf(" read %d no of bytes from n/w(Client/Server) \n",nr);
		if( nr <= 0){
			perror("sockread:");
			free(buf);
			return NULL;
		}
		tbuf = tbuf + nr ;
		nobread += nr;
		if(nobread == n)
			break;
		ntor = ntor - nr;
	}
	return buf;
}

/* This function creates a new socket and binds it to an address and
start's listening on the socket.*/

int connandlisten(int port){
int listfd,retval;
struct sockaddr_in cliaddr, servaddr;
listfd = socket(AF_INET, SOCK_STREAM, 0);
if (listfd < 0){
	perror("sock:");
	return listfd;
}
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(port);
retval = bind(listfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
if(retval < 0){
	perror("bind:");
	close(listfd);
	return -1;
}
listen(listfd, 5);
return listfd;
}
