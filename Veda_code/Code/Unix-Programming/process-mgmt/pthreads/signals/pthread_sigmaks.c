		/*	Creating Multiple threads */


#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sigset_t set;

// Signal handlers for signal 1

void handler1(int i)
{
	printf("\n I am a signal handles for signal %d\n",i);
}

// Signal handlers for signal 2

void handler2(int i)
{
	printf("\n I am a signal handles for signal %d\n",i);	
}

struct my_thread
{
	int thread_id;
 	char mesg[50];	
};


// Routine to initilize my_thread object

void my_init(struct my_thread *obj,int id,char *mesg)
{
	obj->thread_id=id;
        strcpy(obj->mesg,mesg);
}

// Threads created will execute the following routine
void *PrintHello(void *threadobj)
{
	struct my_thread *t1;
	
	t1 = (struct my_thread *) threadobj;
	
	printf("\n Thread ID : %u \t Thread Message %d  %s",pthread_self(),t1->thread_id,t1->mesg); 
	// Block the thread to recive signal
	getchar();
}

int main ()
{
	 pthread_t tid1,tid2,tid3;
	
	 struct my_thread t1,t2,t3;
	 sigemptyset(&set);
	 my_init(&t1,1,"First Thread");
	 my_init(&t2,2,"Second Thread");
	 my_init(&t3,3,"Third Thread");
	 	
	 printf("\n In Default Thread "); 
	 
	
	 sigemptyset(&set);
	
	 // Register handler1 as signal handler for signal 1
	 if(signal(1,handler1)==SIG_ERR)
	 	perror("sig1");
	 // Add signal 1 to sigset object
	 if(sigaddset(&set,1)==-1)
		perror("add1");

	 // Register handler2 as signal handler for signal 2
	 if(signal(2,handler2)==SIG_ERR)
	 	perror("sig2");
	 // Add signal 2 to sigset object
	 if(sigaddset(&set,2)==-1)
	 	perror("add2");

	 // Block signal 1 & 2 in default thread
	 pthread_sigmask(SIG_BLOCK|SIG_SETMASK,&set,NULL);

	 // Create threads
	 printf("\n First thread created \n");	
	 pthread_create(&tid1, NULL, PrintHello,(void *)&t1);
	 pthread_join(tid1,NULL);
	 
	 printf("\n Second thread created\n");	
	 pthread_create(&tid2, NULL, PrintHello,(void *)&t2);
	 pthread_join(tid2,NULL);
	
	 getchar();
	 // Unblock signals before thread 3 is created 
	 pthread_sigmask(SIG_UNBLOCK,&set,NULL);

	 printf("\n Third thread created\n");	
	 pthread_create(&tid3, NULL, PrintHello,(void *)&t3);
	 
	 // send signal 2 to thread 3
	 pthread_kill(tid3,2);
	 pthread_join(tid3,NULL);

	 printf("\n Exit From main Thread\n");
	 pthread_exit(NULL);
}

