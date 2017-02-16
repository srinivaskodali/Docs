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

mqd_t msg_fd;

void open_mqs (void)
{

    /* Open Message Queue */

    if ((msg_fd = mq_open (NAME, O_RDWR, 0, NULL)) == -1)
    {
    	printf ("Failed to open Message Queue\n");    
	exit(1);
    }
    printf ("Message Queue successfully opened\n");    
}



int main()
{
	int i=74;
	char message[BUFSIZE];
	struct mq_attr attr;
	
	open_mqs();	
	
	mq_getattr (msg_fd, &attr);
	printf("\n Total Nuber of messages : %d\n",attr.mq_curmsgs);
	
	while(i>64)
	{
		if (mq_receive (msg_fd, message, BUFSIZE,&i) == -1)
    			printf ("Failed to recive message\n");    
		printf("\n %s - %d\n",message,i);
		i--;		
	}

	mq_close(msg_fd);
	mq_unlink (NAME);
}
