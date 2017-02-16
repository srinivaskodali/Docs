
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>

# define KEY 1234

main(){
	int semid;
	semid = semget(KEY,10,IPC_CREAT);
	printf(" %d is semid\n",semid);
}
