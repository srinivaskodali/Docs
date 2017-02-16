#include <pthread.h>
#include <stdio.h>



// pthread Spinlock object
pthread_spinlock_t spin ; 
// Can also use pthread_rwlock_init (pthread_rwlock_t *, pthread_rwlockattr_t *);

// Threads created will execute the following routines

void * thread1(void *p)
{
	if(pthread_spin_lock(&spin)!=0)
		printf("\n Error :: Spinlock Failed \n");
	else
	{
		printf("\n Thread 1 Aquired spinlock, doing work ....... \n");
		sleep(2);
		pthread_spin_unlock(&spin);
		printf("\n Thread 1 relesed spinlock\n");
	}
	
	pthread_exit(NULL);
}


void * thread2(void *p)
{
	
        printf("\n Thread 2 trying to for spinlock ....... \n");
	if(pthread_spin_lock(&spin)!=0)
                printf("\n Error :: Spinlock Failed \n");
        else
        {
                printf("\n Thread 2 Aquired spinlock, doing work ....... \n");
                pthread_spin_unlock(&spin);
        }

        pthread_exit(NULL);

}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2;
	

	int rv;

	pthread_spin_init(&spin, PTHREAD_PROCESS_SHARED);


	// Routine shell create a new thread
	rv = pthread_create(&tid1, NULL, thread1, NULL);
	if(rv)
		puts("Failed to create thread");

	rv = pthread_create(&tid2, NULL, thread2, NULL);
        if(rv)
                puts("Failed to create thread");


	// suspend execution of the intial thread until the target threads terminates
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	puts(" Exit Main");
	return 0;
}
