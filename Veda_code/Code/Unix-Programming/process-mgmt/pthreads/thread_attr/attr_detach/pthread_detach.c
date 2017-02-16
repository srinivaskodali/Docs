
				/*  explicitly detach a thread even though it was created as joinable */


#include <pthread.h>
#include <stdio.h>
#include <linux/errno.h>


void *thread(void *null)
{
	printf("\n In thread \n");
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	int detach_state,rc;
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	

	pthread_create(&tid, &attr, thread, NULL); 

	sleep(1);
	// explicitly detach thread
	rc = pthread_detach(tid); 	
	
	/* destroy attribute object */
	pthread_attr_destroy(&attr);

	printf("\n Exiting from main Thread\n");
	pthread_exit(NULL);

}


