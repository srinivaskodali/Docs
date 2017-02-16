
					/* get and set scheduling policies & priority of a thread */


#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;


void *thread1(void *str)
{
	int policy;
	struct sched_param param;
	pthread_getschedparam(pthread_self(),&policy,&param);
	printf("\n In thread1 with policy : %d priority : %d \n",policy,param.sched_priority);
	if(pthread_mutex_lock(&mutex)==0)
	{
		sleep(4);
		pthread_getschedparam(pthread_self(),&policy,&param);
		printf("\n thread1 with policy : %d priority : %d Locked mutex\n",policy,param.sched_priority);
		pthread_mutex_unlock(&mutex);
	}
		printf("\n Out of %s \n",(char *)str);
	pthread_exit(NULL);
}




void *thread2(void *str)
{
        int policy;
        struct sched_param param;
        pthread_getschedparam(pthread_self(),&policy,&param);
        printf("\n In thread2 with policy : %d priority : %d \n",policy,param.sched_priority);
        if(pthread_mutex_lock(&mutex)==0)
        {
                sleep(4);
                pthread_getschedparam(pthread_self(),&policy,&param);
                printf("\n In thread2 with policy : %d priority : %d Locked mutex\n",policy,param.sched_priority);
                pthread_mutex_unlock(&mutex);
        }
                printf("\n Out of %s \n",(char *)str);
        pthread_exit(NULL);
}



// writes scheduling policy of given thread attribute object
void write_schedpolicy(pthread_attr_t *attr,int policy)
{
	// Sets scheduling policy of attribute object
	pthread_attr_setschedpolicy(attr,policy);
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
	int inherit,policy,priority,rc,old;
        struct sched_param param;
	pthread_mutexattr_t mattr;
	pthread_t tid1,tid2;
	pthread_attr_t attr;

	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_setprotocol(&mattr,PTHREAD_PRIO_INHERIT);
	pthread_mutex_init(&mutex,&mattr);
	pthread_attr_init(&attr);
	
	// Sets inheritsched attribute 
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);


	write_schedpolicy(&attr,SCHED_FIFO);
	write_schedparam(&attr,4);

	
	pthread_create(&tid1, &attr, thread1, "Priority 4");
	
	write_schedpolicy(&attr,SCHED_FIFO);
	write_schedparam(&attr,8);

	pthread_create(&tid2, &attr, thread2, "Priority 8");

	rc = pthread_join(tid1,NULL); 	
	rc = pthread_join(tid2,NULL); 	
	
	/* destroy attribute object */
	pthread_attr_destroy(&attr);

	printf("\n Exiting from main Thread\n");
	pthread_exit(NULL);

}


