#include <pthread.h>
#include <stdio.h>
//#include "check.h"

void *threadfunc(void *parm)
{
	int i=25;
  //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  //pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

  printf("Entered secondary thread\n");
  while (1) {
    printf("Secondary thread is looping\n");
    while(i<=6000)
    {
	printf("\n CHILD : %d ",i++);
//	sleep(1);
    }
	pthread_testcancel();
    sleep(1);
  }
  //  pthread_testcancel();
  return NULL;
}

int main(int argc, char **argv)
{
  pthread_t             thread;
  int                   rc=0,i=0;

  printf("Entering testcase\n");
  
  /* Create a thread using default attributes */
  printf("Create thread using the NULL attributes\n");
  rc = pthread_create(&thread, NULL, threadfunc, NULL);
  //checkResults("pthread_create(NULL)\n", rc);
  
  sleep(1);
  printf("\n MAIN : Cancel the CHILD thread\n");
  rc = pthread_cancel(thread);
  while(i<=20)
	printf("\n %d ",i++);
  printf("\n MAIN : CHILD Cancled \n");
  pthread_join(thread,NULL);
  //sleep(3);
  printf("Main completed\n");
  return 0;
}
