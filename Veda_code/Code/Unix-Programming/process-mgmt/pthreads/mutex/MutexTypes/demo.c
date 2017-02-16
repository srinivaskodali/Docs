		/*	Example for implementing errorcheck mutex */
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

char str[50];

// pthread mutex object
pthread_mutex_t mutex;

// Threads created will execute the following routines
 
void * write_thread (void *p)
{
	int rv;
	printf("\n In Write thread\n");
	if((rv = pthread_mutex_lock(&mutex))==0)
	{
		printf("\n Write job Critical Section\n");
		getchar();		
		pthread_exit(NULL);
	}
}

void * read_thread(void *p)
{
	int rv;
	printf("\n In Read thread \n");
	
	rv = pthread_mutex_lock(&mutex);
	if(rv==EOWNERDEAD)
		printf("\n Owner Dead\n");
	else if (rv == 0)
	{
        	printf(" %s \n",str);
		pthread_mutex_unlock(&mutex);
	}
	printf(" Read job is over\n");
        pthread_exit(NULL);
}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2;

	// Mutex Attribute object
	pthread_mutexattr_t attr;
	int rv;

	// initializing mutex attribute object 
	pthread_mutexattr_init(&attr);

	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_ROBUST_NP);
	// initializing statically allocated mutex object 
	pthread_mutex_init(&mutex,&attr);
	
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
