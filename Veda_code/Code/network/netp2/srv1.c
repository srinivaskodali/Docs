/* Example showing how to implement tcp/ip server.
   Using select api

   Version: 1.0
   Author : Team -C
*/

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    fd_set readset, testset;
    int listensock;
    int newsock;
    char buffer[25];
    int result;
    int nread;
    int x;
    
    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    result = bind(listensock, (struct sockaddr *) &servaddr, sizeof(servaddr));
   if (result < 0) {
        perror("server1");
        return 0;
    }

    result = listen(listensock, 5);
    if (result < 0) {
        perror("server1");
        return 0;
    }

    FD_ZERO(&readset);
    FD_SET(listensock, &readset);

    while (1) {
        testset = readset;
        result = select(FD_SETSIZE, &testset, NULL, NULL, NULL);
        if (result < 1) {
            perror("server1");
            return 0;
        }
        for (x = 0; x < FD_SETSIZE; x++) {
            if (FD_ISSET(x, &testset)) {
                if (x == listensock) {
                    newsock = accept(listensock, NULL ,NULL);
                    FD_SET(newsock, &readset);
                } else {
		      nread=read(newsock,buffer,25);	
                    if (nread <= 0) {
                        close(x);
                        FD_CLR(x, &readset);
                        printf("client on descriptor #%i disconnected\n", x);
                    } else {
                        buffer[nread] = '\0';
                        printf("%s\n", buffer);
                        write(x, buffer, nread);
                    }  
                }
            }
        }
    }
}
