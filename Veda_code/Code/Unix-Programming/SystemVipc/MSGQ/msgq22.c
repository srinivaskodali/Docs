/* example showing how to create msgq.
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>

# define KEY 8979

typedef struct{
	long msgtype;
	char buffer[100];
}msg;
main(){
	int qid;
	int i;
	msg m1,m2;
	qid = msgget(KEY,IPC_CREAT);
	i = msgrcv(qid,&m1,sizeof(msg),10,0);
	for(i=0;i<100;i++)
		printf("%c",m1.buffer[i]);
	printf("\n");
	i = msgrcv(qid,&m2,sizeof(msg),20,0);
	for(i=0;i<100;i++)
		printf("%c",m2.buffer[i]);
	printf("\n");
}
