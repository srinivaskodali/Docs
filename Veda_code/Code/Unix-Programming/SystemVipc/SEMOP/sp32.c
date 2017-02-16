
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>

# define KEY 1234

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

main(){
	int semid,retval;
	struct sembuf *sbuf;
	sbuf = (struct sembuf*) malloc(sizeof(struct sembuf));
	semid = semget(KEY,1,IPC_CREAT);
	sbuf->sem_num = 0;
	sbuf->sem_op = 1; // add this value to semaphore.
	sbuf->sem_flg = SEM_UNDO; // IPC_NOWAIT can be used.
	semop(semid,sbuf,1);
	perror("aa");
}
