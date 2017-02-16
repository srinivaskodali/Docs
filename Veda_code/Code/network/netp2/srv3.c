/* Exampe showing how to implement tcp/ip server.
Using Preforking ( creating a pool of process and selecting one process from the pool when connection occurs)
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
    int listensock;
    int newsock;
    char buffer[25];
    int result;
    int nread;
    int pid;
    int nchildren = 1;
    int x;
    int val;	
    if (argc > 1) {
        nchildren = atoi(argv[1]);
    }

    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    result = bind(listensock, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (result < 0) {
        perror("exserver3");
        return 0;
    }

    result = listen(listensock, 5);
    if (result < 0) {
        perror("exserver3");
        return 0;
    }

    for (x = 0; x < nchildren; x++) {
        if ((pid = fork()) == 0) {
            while (1) {
                newsock = accept(listensock, NULL ,NULL);
                printf("client connected to child process %i.\n", getpid());
                nread=read(newsock,buffer,25);
                buffer[nread] = '\0';
                printf("%s\n", buffer);
                write(newsock, buffer, nread);
                close(newsock);
                printf("client disconnected from child process %i.\n", getpid());
            }
        }
    }

    wait(NULL);
}
