		/*	Example for implementing mutex for locking resources */
#include <pthread.h>
#include <stdio.h>


char str[50];

// pthrepad mutex object
// initializing statically allocated mutex object 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Threads created will execute the following routines
 
void * write_thread (void *p)
{
	printf("\n In Write thread\n");
	if(pthread_mutex_lock(&mutex)==0)
	{
		printf(" Enter A string : ");
		 fgets(str,49,stdin);
		printf("\n Write job is over\n");
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);	
}

void * read_thread(void *p)
{
	if(pthread_mutex_trylock(&mutex)==0)
	{
       		printf("\n In Read thread \n");
        	printf(" %s \n",str);
		pthread_mutex_unlock(&mutex);
	}
	else
		printf("\n Mutex in not avaliable...");
	
	printf(" Continue remaining job \n");
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
