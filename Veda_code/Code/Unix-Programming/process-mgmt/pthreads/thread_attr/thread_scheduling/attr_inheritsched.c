
					/* get and set the inheritsched attributes */


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
	int inherit,policy,priority,rc;
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	
	// Gets inheritsched attribute 
	pthread_attr_getinheritsched(&attr,&inherit);
	// 0 - PTHREAD_INHERIT_SCHED 1 - PTHREAD_EXPLICIT_SCHED
	printf("\n Default inherit State : %d\n",inherit);

	
	// Sets inheritsched attribute 
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);

	// Gets inheritsched attribute 
	pthread_attr_getinheritsched(&attr,&inherit);
	// 0 - PTHREAD_INHERIT_SCHED 1 - PTHREAD_EXPLICIT_SCHED
	printf("\n inherit State : %d\n",inherit);
	
        pthread_create(&tid, &attr, thread, NULL);

	rc = pthread_join(tid,NULL); 	
	if(rc == EINVAL)
		printf("\n Error : Cannot join detached thread\n ");
	
	/* destroy attribute object */
	pthread_attr_destroy(&attr);

	printf("\n Exiting from main Thread\n");
	pthread_exit(NULL);

}


