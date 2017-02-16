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
	if(pthread_mutex_lock(&mutex)==0)
	{
        	if(rv==EOWNERDEAD)
        	{
        	        printf("\n Owner Dead\n");
			pthread_mutex_consistent_np(&mutex);
        	}
		printf("\nWrite thread: Writing....\n");
		pthread_exit(NULL);
	}
}

void * read_thread1(void *p)
{
	int rv;
	printf("\n In Read1 thread \n");
	rv = pthread_mutex_lock(&mutex);
	{
		if(rv == EOWNERDEAD)
		{
			printf("\n Owner Dead\n");
			pthread_mutex_consistent_np(&mutex);
			pthread_mutex_unlock(&mutex);
		}
		else
		{
	       		printf(" %s \n",str);
			pthread_mutex_unlock(&mutex);
		}
	}
        pthread_exit(NULL);
}

void * read_thread2(void *p)
{
        int rv;
	sleep(2);
        printf("\n In Read2 thread \n");

        rv = pthread_mutex_lock(&mutex);
        if(rv==EOWNERDEAD)
        {
                printf("\n Owner Dead\n");
		pthread_mutex_consistent_np(&mutex);
        }
        else if (rv == 0)
        {
                printf(" Lock aquaired \n");
                pthread_mutex_unlock(&mutex);
        }
        pthread_exit(NULL);
}


int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2,tid3;

	// Mutex Attribute object
	pthread_mutexattr_t attr;
	int rv;

	// initializing mutex attribute object 
	pthread_mutexattr_init(&attr);

//	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_ROBUST_NP);
	// initializing statically allocated mutex object 
	pthread_mutexattr_setrobust_np(&attr, PTHREAD_MUTEX_ROBUST_NP);
	pthread_mutex_init(&mutex,&attr);

	
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
	pthread_join(tid3,NULL);
	puts(" Exit Main");
	return 0;
}
