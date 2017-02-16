
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
	union semun su,su1;
	semid = semget(KEY,10,IPC_CREAT);
/* set the value of first sem in set to 1 */
	su.val=2;
	retval = semctl(semid,0,SETVAL,su);
	printf(" Value in sem 0 = %d\n",retval);
/* to get the value of the sem. */
	retval = semctl(semid,0,GETVAL,su1);
	printf(" Value in sem 0 = %d\n",retval);
	getchar();
}
