		/*	one thread waiting for other thread to termination */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Thread created will execute the following routine
 
void * thread_routine1 (void *p)
{
   static unsigned int exit  = 1;	
   printf("\n I am in thread 1\n");	
   pthread_exit((void *) &exit);	
}

void * thread_routine2 (void *p)
{
   static unsigned int exit  = 2;	
   printf("\n I am in thread 2\n");
   pthread_exit((void *) &exit);	
}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2;
	int rv, *exit1,*exit2;
	// Routine shell create a new thread
	rv = pthread_create(&tid1, NULL, thread_routine1, NULL);
	if(rv)
		puts("Failed to create thread");

	rv = pthread_create(&tid2, NULL, thread_routine2, NULL);
        if(rv)
                puts("Failed to create thread");

	// suspend execution of the intial thread until the target threads terminates
	pthread_join(tid1,(void **)&exit1);
	pthread_join(tid2,(void **)&exit2);
	printf("\n Exit status of Thread1 : %d\n",*exit1);
	printf("\n Exit status of Thread2 : %d\n",*exit2);
	puts(" Exit Main");
	return 0;
}
