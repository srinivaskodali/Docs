#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <mqueue.h>

#define BUFSIZE 50
#define NAME "/my_mq"

size_t size = BUFSIZE;

struct mq_attr attr = {
    .mq_maxmsg = 10,
    .mq_msgsize = BUFSIZE,
};




mqd_t msg_fd;

void create_mqs (void)
{

    /* Creating Message Queue */

    if ((msg_fd = mq_open (NAME, O_RDWR | O_CREAT | O_EXCL, 0666, &attr)) == -1)
    {
    	printf ("Failed to create Message Queue\n");    
	exit(1);
    }
    printf ("Message Queue successfully created\n");    
}



int main()
{
	int i=65;
	char message[BUFSIZE];
	create_mqs();	
	
	while(i<75)
	{
		memset(message,(char)i,BUFSIZE-1);
		//message[BUFSIZE]='\0';
		printf("\n %s - %d\n",message,i);
		if (mq_send (msg_fd, message, BUFSIZE, i) == -1)
    			printf ("Failed to send message\n");    
		i++;		
	}

	mq_close(msg_fd);
}
