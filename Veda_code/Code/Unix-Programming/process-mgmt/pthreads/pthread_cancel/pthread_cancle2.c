
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *PrintHello(void *threadid)
{
	int state,type,state1=PTHREAD_CANCEL_DISABLE,type1=PTHREAD_CANCEL_ASYNCHRONOUS;
	printf("\nHello World!\n");
	pthread_setcancelstate(state1,NULL)==0;
	if(pthread_setcancelstate((int)NULL,&state)==0)
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
	pthread_setcanceltype(type1,NULL);
	if(pthread_setcanceltype((int)NULL,&type)==0)
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
    	pthread_testcancel();
	printf("\n After Cancle\n");
	while(1);
	printf("\n Exit from thread\n");

	
}

int main ()
{
	 pthread_t thread;
	 int rc, t=0;
	 printf("Creating thread %d\n", t);
	 rc = pthread_create(&thread, NULL, PrintHello, NULL);
	 printf("\n Thread ID : %u",thread);
	 sleep(4);
   	 t=pthread_cancel(thread); 
	 //pthread_join(thread,NULL);
	 printf("\n Thread ID : %u\n",thread);

}

