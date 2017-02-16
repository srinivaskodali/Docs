/* Test of POSIX barriers.  */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int a[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
pthread_barrier_t barr;

void * thread1(void *arg)
{
	int i ,sum = 0,rc;
	for(i=0;i<5;i++)
		sum+=a[i];
	printf("\n Thread1 waits at barrier\n");
	rc =  pthread_barrier_wait(&barr);
	printf("\n Thread1 resume\n");
	printf("\n 1 - %d \n",sum);
	printf("\n Thread1 terminates\n");
}

void * thread2(void *arg)
{
	int i ,sum = 0;
        for(i=5;i<10;i++)
	{
                sum+=a[i];
	}
	printf("\n Thread2 waits at barrier\n");
		sleep(1);
         pthread_barrier_wait(&barr);
	printf("\n Thread2 resume\n");
	printf("\n 2 - %d \n",sum);
	printf("\n Thread2 terminates\n");

}

void * thread3(void *arg)
{
	int i ,sum = 0;
        for(i=10;i<15;i++)
	{
		sum+=a[i];
	}
	printf("\n Thread3 waits at barrier\n");
         	sleep(2);
         pthread_barrier_wait(&barr);
	printf("\n Thread3 resume\n");
	printf("\n 3 - %d \n",sum);
	printf("\n Thread3 terminates\n");

}

int main()
{
	pthread_t tid1,tid2,tid3;
	// Barrier initialization
	if(pthread_barrier_init(&barr, NULL, 3))
	{
        	printf("Could not create a barrier\n");
        	return -1;
    	}
	pthread_create(&tid1, NULL, thread1, NULL);
	pthread_create(&tid1, NULL, thread2, NULL);
	pthread_create(&tid1, NULL, thread3, NULL);


	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);


}
