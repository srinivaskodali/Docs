		/*	Creating Multiple threads */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_thread
{
	int thread_id;
 	char mesg[100];	
};
void *PrintHello(void *threadobj)
{
	pthread_t thread_ID;
	struct my_thread *t1;
	t1 = (struct my_thread *) threadobj;
	thread_ID = pthread_self();
	printf("\n Thread ID : %u",thread_ID); 
	printf("\n %d Thread Message : %s\n",t1->thread_id,t1->mesg); 	
}

int main ()
{
	 pthread_t thread2,thread3,thread4,thread_ID;
	 int rc;
	 struct my_thread t2,t3,t4;
	 t4.thread_id=4;
	 strcpy(t4.mesg,"I am Forth Thread\n");
	 t2.thread_id=2;
	 strcpy(t2.mesg,"I am Second Thread\n");
	 t3.thread_id=3;
	 strcpy(t3.mesg,"I am Third Thread\n");
	 	
	 thread_ID = pthread_self();
	 printf("\n MAIN Thread ID : %u",thread_ID); 

	 rc = pthread_create(&thread4, NULL, PrintHello,(void *)&t4);
	 rc = pthread_create(&thread2, NULL, PrintHello,(void *)&t2);
	 //thread_ID = pthread_self();
	 //printf("\n Thread ID : %d",thread_ID); 
	 rc = pthread_create(&thread3, NULL, PrintHello,(void *)&t3);
	 //thread_ID = pthread_self();
	 //printf("\n Thread ID : %d",thread_ID); 

	if (rc)
	 {
         	printf("ERROR; return code from pthread_create() is %d\n", rc);
	        exit(-1);
	 }
	 printf("\n Exit From main Thread\n");
	 pthread_exit(NULL);
}

