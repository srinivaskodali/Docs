		/*	PThread Creation & Tremination without pthread_exit routine	*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Thread created will execute the following routine
 
void * thread_routine1 (void *p)
{
   getchar();	
   printf("\nI am %d threads\n",*(int *)p);
}

void * thread_routine2 (void *p)
{
   printf("\nI am %d threads\n",*(int *)p);
}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2;
	int rv;
	int arg1 =1,arg2 = 2;	
	// Routine shell create a new thread
	rv = pthread_create(&tid1, NULL, thread_routine1, &arg1);
	if(rv)
		puts("Failed to create thread");

	rv = pthread_create(&tid2, NULL, thread_routine2, &arg2);
        if(rv)
                puts("Failed to create thread");

	puts("Exit Main");
	/* Terminate process with exit(0) after termination of all threads */
	pthread_exit(NULL);
}
