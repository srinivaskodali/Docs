/* Example showing how to implement tcp/ip server.
	Prethreaded example ( pool of threads, one thread is selected form the pool)
	Version: 1.0
	Author : Team -C
*/

#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void* thread_proc(void *arg);

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int listensock;
    int result;
    int nchildren = 1;
    pthread_t thread_id;
    int x;
    
    if (argc > 1) {
      nchildren = atoi(argv[1]);
    }

    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    result = bind(listensock, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (result < 0) {
        perror("exserver5");
        return 0;
    }

    result = listen(listensock, 5);
    if (result < 0) {
        perror("exserver5");
        return 0;
    }

   for (x = 0; x < nchildren; x++) {
	result = pthread_create(&thread_id, NULL, thread_proc, (void *) listensock);
	if (result != 0) {
	  printf("Could not create thread.\n");
	  return 0;
	}
	sched_yield();
    }

   pthread_join (thread_id, NULL);
}

void* thread_proc(void *arg)
{
  int listensock, sock;
  char buffer[25];
  int nread;

  listensock = (int) arg;

  while (1) {
    sock = accept(listensock, NULL, NULL);
    printf("client connected to child thread %i with pid %i.\n", pthread_self(), getpid());
    nread = read(sock, buffer, 25);
    buffer[nread] = '\0';
    printf("%s\n", buffer);
    write(sock, buffer, nread);
    close(sock);
    printf("client disconnected from child thread %i with pid %i.\n", pthread_self(), getpid());
  }
}
