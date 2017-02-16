/*	initialize & destroy  a  thread  attributes  object	*/

#include <pthread.h>
#include <stdio.h>

// Thread created will execute the following routine
 
void * thread_routine (void *p)
{
	char *str = (char *)p;
	printf("\nMessage to thread : %s \n",str);
}

int main ()
{
	pthread_t thread;

	// Thread attribute object
	pthread_attr_t pattr;
	int rv;
	
	// Routine shall initialize a thread attributes object
	rv = pthread_attr_init(&pattr);
	if(rv)
		puts("Failed to initialize thread attribute object");
	
	rv = pthread_create(&thread, &pattr, thread_routine, "Argument to thread");

	// Routine shall destroy a thread attributes object
	rv = pthread_attr_destroy(&pattr);
	if(rv)
		puts("Failed to destroy thread attribute object");

	puts("Exit Main");
	pthread_exit(NULL);	
}
