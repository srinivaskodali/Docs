		/*	PThread Creation & Tremination without pthread_exit routine	*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Thread created will execute the following routine
 
void * thread_routine (void *p)
{
   printf("\nHello World!\n");
}

int main ()
{
	// Object to hold thread ID
	pthread_t thread;
	int rv;
	
	// Routine shell create a new thread
	rv = pthread_create(&thread, NULL, thread_routine, NULL);
	if(rv)
		puts("Failed to create thread");

	puts("Exit Main");
	pthread_exit(NULL);	
}
