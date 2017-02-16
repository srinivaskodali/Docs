
					/* get and set the detachstate attribute */


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
	
	// Gets Default Detach State 
	pthread_attr_getdetachstate(&attr,&detach_state);
	
	// 0 - Joinable State	1 - Detach State
	printf("\n Default Detach State : %d\n",detach_state);

	/* set thread detached attribute to detached state */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&tid, &attr, thread, NULL); 

	// Cannot join threads created with detached state
	rc = pthread_join(tid,NULL); 	
	if(rc == EINVAL)
		printf("\n Error : Cannot join detached thread\n ");
	
	/* destroy attribute object */
	pthread_attr_destroy(&attr);

	printf("\n Exiting from main Thread\n");
	pthread_exit(NULL);

}


