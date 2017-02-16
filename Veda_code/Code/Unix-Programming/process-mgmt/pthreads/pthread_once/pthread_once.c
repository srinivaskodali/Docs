#include<pthread.h>
#include<stdio.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void *myinit() // executes only once fro first thread
{
	printf("\n I am in init fun\n");
}
void *mythread(void *i)
{
	printf("\n I am in mythread : %d\n",*(int *)i);
	pthread_once(&once,(void *)myinit);
	printf("\n Exit from mythread : %d\n",*(int *)i);
}
int main()
{
	int id = 1;
	pthread_t thread,thread1,thread2;
	pthread_create(&thread,NULL,mythread,(void *)&id);
	pthread_join(thread,NULL);
	id++;
	pthread_create(&thread1,NULL,mythread,(void *)&id);	
	pthread_join(thread1,NULL);
	id++;
	pthread_create(&thread2,NULL,mythread,(void *)&id);	
	printf("\n Exit For Main Thread\n");
	pthread_exit(NULL);
}
	
