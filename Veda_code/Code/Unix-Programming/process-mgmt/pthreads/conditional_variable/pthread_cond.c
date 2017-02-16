		/*	Example for implementing conditional variables for signaling b/n threads */
#include <pthread.h>
#include <stdio.h>


char str[50];



typedef struct 
{
	// pthread mutex object
	pthread_mutex_t mutex;
	// pthread conditonal variable 
	pthread_cond_t cond;
	unsigned short conditionMet;
} my_lock_t;

my_lock_t lock = {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,0}; 

// Threads created will execute the following routines
 
void * write_thread (void *p)
{
	printf("\n In Write thread\n");
	if(lock.conditionMet==0)
	{
		if(pthread_mutex_lock(&lock.mutex)==0)
		{
			printf(" Enter A string : ");
			 read(0,str,49);
			printf("\n Write job is over\n");
			lock.conditionMet = 1;
			pthread_cond_signal(&lock.cond);
			pthread_mutex_unlock(&lock.mutex);
		}
	}
	pthread_exit(NULL);	
}

void * read_thread(void *p)
{
	
       	printf("\n In Read thread \n");
	if(lock.conditionMet!=1)
	{
		pthread_cond_wait(&lock.cond,&lock.mutex);
	}
        printf(" %s \n",str);
	pthread_mutex_unlock(&lock.mutex);
	
	printf(" Read job is over\n");
        pthread_exit(NULL);
}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2;
	int rv;
	// Routine shell create a new thread
	rv = pthread_create(&tid1, NULL, write_thread, NULL);
	if(rv)
		puts("Failed to create thread");

	rv = pthread_create(&tid2, NULL, read_thread, NULL);
        if(rv)
                puts("Failed to create thread");

	// suspend execution of the intial thread until the target threads terminates
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	puts(" Exit Main");
	return 0;
}
