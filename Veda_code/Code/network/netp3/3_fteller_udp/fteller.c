/* Example showing how to implement a protocol in our  server.
Version: 1.0
Author : Team -C
Note : Write a function which reads till it receives the chars r followed by s.
*/
# include "lib1.h"
# include <stdio.h>
# include <stdlib.h>


/* following function will be handling the client in child process */

void handleClient(int connfd){
	struct sockaddr_in servaddr;
	socklen_t addr_len;
	char *hellomsg = "Welcome to FT. what's your name";
	char *fm[] = {"you will get good score in exam",\
"you will get job",\
"blah.. blah.."};
	int n,i,fortune_no=0;
	short *s;
	char *buf;
	short size;
// according to (2) in protocol.
	size = strlen(hellomsg);
	//write(connfd,&size,2);
	sendto(connfd,&size,2,0,(struct sockaddr *)&servaddr,addr_len);
	//write(connfd,hellomsg,size);
	sendto(connfd,hellomsg,size,0,(struct sockaddr *)&servaddr,addr_len);
// according to step (3)
	s = (short *)readNBytes(connfd,2);	
	buf = readNBytes(connfd,*s);
	for(i=0;i<*s;i++,buf++){
		fortune_no += *buf;
		printf("%c",*buf);
	}
	printf("\n");
	fortune_no %=3;
// according to step (3);
	printf(" fortune_no = %d\n",fortune_no);
	size = strlen(fm[fortune_no]);
//	write(connfd,&size,2);
	sendto(connfd,&size,2,0,(struct sockaddr *)&servaddr,addr_len);
//	write(connfd,fm[fortune_no],size);
	sendto(connfd,fm[fortune_no],size,0,(struct sockaddr *)&servaddr,addr_len);

//	exit(0); // terminate child.
}

main(){
	int connfd,retval;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	connfd = connandlisten(9000);
	clilen = sizeof(struct sockaddr_in);
	while(1){
		char buf[200];
		pid_t p;
		int n;
		//clilen = sizeof(cliaddr);
		//connfd = accept(listfd, (struct sockaddr *) &cliaddr, &clilen);
		printf(" client connected \n");
		//p = fork();
		//if( p == 0){
			//close(listfd);
			handleClient(connfd);
		//}
	}
	close(connfd);
}
