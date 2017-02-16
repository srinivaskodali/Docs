
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void *PrintHello(void *threadid)
{
	int state,type,ref;
	printf("\nHello World!\n");
	
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	if(pthread_setcancelstate((int )NULL,&state)==0)
	{
		switch(state)
		{
			case PTHREAD_CANCEL_ENABLE:
				printf("\n Cancel State Enable\n");
				break;
			case PTHREAD_CANCEL_DISABLE:
				printf("\n Cancel State Disable\n"); 
		}
	}
	if(pthread_setcanceltype((int )NULL,&type)==0)
	{
		switch(type)
		{
			case PTHREAD_CANCEL_DEFERRED:
				printf("\n Cancel Type Deferred\n");
				break;
			case PTHREAD_CANCEL_ASYNCHRONOUS:
				printf("\n Cancel Type Asynchoronous\n"); 
		}
	}
	sleep(3);	
	printf("\n Statement Before Testcancle\n");
   	//pthread_testcancel();
	printf("\n STATEMENT AFTER TESTCANCLE\n");
	//sleep(5);
   while(1);
	printf("\n In thread\n");		
	pthread_exit(0);
}

int main ()
{
	 pthread_t thread;
	 int rc, t=0;
	 printf("Creating thread %d\n", t);
	 rc = pthread_create(&thread, NULL, PrintHello, NULL);
	 printf("\n Thread ID : %u",thread);
	 sleep(1);
   	 pthread_testcancel();
    	 /*if(t==0)
		printf("\n cancel request sent to thread\n");*/
	 printf("\n Thread ID : %u\n",thread);
   	// pthread_cancel(thread);
	// pthread_join(thread,NULL); 
	 printf("\n Cancled the thread\n");
	 if (rc)
	 {
         	printf("ERROR; return code from pthread_create() is %d\n", rc);
	        exit(-1);
	 }
	 printf("\n Exit From main  Thread\n");
	 pthread_exit(NULL);
}

