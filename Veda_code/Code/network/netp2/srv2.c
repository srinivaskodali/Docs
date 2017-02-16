
/* Example showing how to implement tcp/ip server.
	Fork based server ( one child-process per client upon accept
	Version: 1.0
	Author : Team -C
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int signo)
{
  while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int listensock;
    int newsock;
    char buffer[25];
    int result;
    int nread;
    int pid;
    int val;
    
    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    val = 1;
    result = setsockopt(listensock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (result < 0) {
        perror("server2");
        return 0;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    result = bind(listensock, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (result < 0) {
        perror("exserver2");
        return 0;
    }

    result = listen(listensock, 5);
    if (result < 0) {
        perror("exserver2");
        return 0;
    }

    signal(SIGCHLD, sigchld_handler);

    while (1) {
        newsock = accept(listensock, NULL ,NULL);
        if ((pid = fork()) == 0) {
            printf("child process %i created.\n", getpid());
            close(listensock);
            nread = read(newsock,buffer,25);
            buffer[nread] = '\0';
            printf("%s\n", buffer);
            write(newsock, buffer, nread);
            close(newsock);
            printf("child process %i finished.\n", getpid());
            exit(0);
        }
        close(newsock);
    }
}
