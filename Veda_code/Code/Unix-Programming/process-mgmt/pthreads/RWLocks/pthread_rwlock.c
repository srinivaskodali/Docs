		/*	Example for implementing mutex for locking resources */
#include <pthread.h>
#include <stdio.h>


char str[50];

// pthread Read/Write Lock object
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER; 
// Can also use pthread_rwlock_init (pthread_rwlock_t *, pthread_rwlockattr_t *);

// Threads created will execute the following routines
 
void * write_thread (void *p)
{
	/* To lock Rewad/Write Lock for writing use any one of the following 
			pthread_rwlock_wrlock (pthread_rwlock_t *);
			pthread_rwlock_trywrlock (pthread_rwlock_t *);
			pthread_rwlock_timedwrlock (pthread_rwlock_t *,struct timespec *); */
			
	if(pthread_rwlock_wrlock(&rwlock)!=0)
		printf("\n Error :: Failed to Aquire Write Lock\n");
	else
	{
		printf("Successfully Aquired Write Lock\nWriting .........\n");
		sleep(1);
		pthread_rwlock_unlock(&rwlock);
	}	
	pthread_exit(NULL);	
}

void * read_thread1(void *p)
{
	 /* To lock Rewad/Write Lock for Reading use any one of the following 
                        pthread_rwlock_rdlock (pthread_rwlock_t *);
                        pthread_rwlock_tryrdlock (pthread_rwlock_t *);
                        pthread_rwlock_timedrdlock (pthread_rwlock_t *,struct timespec *); */

	if(pthread_rwlock_rdlock(&rwlock)!=0)
		printf("\n Error :: Failed to Aquire Read Lock\n");
	else
	{
		printf("Thread 1 Successfully Aquired Read Lock\nReading .........\n");
		sleep(2);
		pthread_rwlock_unlock(&rwlock);
	}
	printf(" Read1 job is over\n");
        pthread_exit(NULL);
}


void * read_thread2(void *p)
{
	if(pthread_rwlock_rdlock(&rwlock)!=0)
                printf("\n Error :: Failed to Aquire Read Lock\n");
        else
        {
                printf("thread 2 Successfully Aquired Read Lock\nReading .........\n");
                sleep(2);
                pthread_rwlock_unlock(&rwlock);
        }
        printf(" Read2 job is over\n");
        pthread_exit(NULL);

}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2,tid3;
	

	int rv;
	

	
	// Routine shell create a new thread
	rv = pthread_create(&tid1, NULL, write_thread, NULL);
	if(rv)
		puts("Failed to create thread");

	rv = pthread_create(&tid2, NULL, read_thread1, NULL);
        if(rv)
                puts("Failed to create thread");

	rv = pthread_create(&tid3, NULL, read_thread2, NULL);
        if(rv)
                puts("Failed to create thread");

	// suspend execution of the intial thread until the target threads terminates
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	puts(" Exit Main");
	return 0;
}
