
					/* get and set scheduling policies & priority of a thread */


#include <pthread.h>
#include <stdio.h>

void *thread(void *null)
{
	int policy;
	struct sched_param param;
	printf("\n In thread \n");
	pthread_getschedparam(pthread_self(),&policy,&param);
	printf("\n Thread Policy : %d Priority : %d",policy,param.sched_priority);
	printf("\n Maximum priority for SCHED_FIFO : %d",sched_get_priority_max(SCHED_FIFO));
	printf("\n Minimum priority for SCHED_FIFO : %d\n",sched_get_priority_min(SCHED_FIFO));
	printf("\n Maximum priority for SCHED_RR : %d",sched_get_priority_max(SCHED_RR));
	printf("\n Minimum priority for SCHED_RR : %d",sched_get_priority_min(SCHED_RR));
	pthread_exit(NULL);
}


// reads scheduling policy of given thread attribute object
void read_schedpolicy(pthread_attr_t *attr)
{
	int policy;
	// Gets scheduling policy of attribute object
	pthread_attr_getschedpolicy(attr,&policy);
	// 0 - SCHED_OTHERS	1 - SCHED_FIFO		2 - SCHED_RR		
	printf("\n Scheduling Policy : %d",policy)	;
}

// writes scheduling policy of given thread attribute object
void write_schedpolicy(pthread_attr_t *attr,int policy)
{
	// Sets scheduling policy of attribute object
	pthread_attr_setschedpolicy(attr,policy);
}

// reads scheduling priority of given thread attribute object
void read_schedparam(pthread_attr_t *attr)
{
	struct sched_param param;
	pthread_attr_getschedparam(attr,&param);
	printf("\n thread priority : %d \n", param.sched_priority);
}

// wriets scheduling priority of given thread attribute object
void write_schedparam(pthread_attr_t *attr,int priority)
{
	struct sched_param param;
	param.sched_priority = priority;
	pthread_attr_setschedparam(attr,&param);
}



int main (int argc, char *argv[])
{
	int inherit,policy,priority,rc;
        struct sched_param param;

	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	
	// Sets inheritsched attribute 
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);

	read_schedpolicy(&attr);
	read_schedparam(&attr);

	write_schedpolicy(&attr,SCHED_FIFO);
	write_schedparam(&attr,4);

	read_schedpolicy(&attr);
	read_schedparam(&attr);
	
	pthread_create(&tid, &attr, thread, NULL);

	rc = pthread_join(tid,NULL); 	
	
	/* destroy attribute object */
	pthread_attr_destroy(&attr);

	printf("\n Exiting from main Thread\n");
	pthread_exit(NULL);

}


