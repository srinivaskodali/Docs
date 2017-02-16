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

main(){
	int qid;
	qid = msgget(KEY,IPC_CREAT);
	printf(" qid = %d\n", qid);
	getchar();
	msgctl(qid,IPC_RMID,NULL);
}
