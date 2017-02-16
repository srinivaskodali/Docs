
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *PrintHello(void *threadid)
{
	printf("\nHello World!\n");
   while(1);
}

int main ()
{
	 pthread_t thread;
	 int rc, t=0;
	 printf("Creating thread %d\n", t);
	 rc = pthread_create(&thread, NULL, PrintHello, NULL);
	 printf("\n Thread ID : %u",thread);
	 sleep(6);
   	 t=pthread_cancel(thread);
    	 if(t==0)
		printf("\n Thread %u cancled \n",thread);
	 printf("\n Thread ID : %u\n",thread);
	if (rc)
	 {
         	printf("ERROR; return code from pthread_create() is %d\n", rc);
	        exit(-1);
	 }
	 printf("\n Exit from Main\n");
}

