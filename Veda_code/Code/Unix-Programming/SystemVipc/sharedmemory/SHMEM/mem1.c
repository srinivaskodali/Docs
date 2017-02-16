/* shows how to use shared memory
Version : 1.0
Author : Team -C
*/

# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/types.h>

main(){
	int shm_id;
	key_t key = 99999;
	shm_id = shmget(key,8000,IPC_CREAT);
	if(shm_id <0){
		perror("shmget:");
		exit(1);
	}
	printf("shm_id = %d\n",shm_id);
/*	shm_id = shmget(key,8000,IPC_CREAT|IPC_EXCL);
	if(shm_id <0){
		perror("shmget:");
		exit(1);
	}
	printf("shm_id = %d\n",shm_id);*/
	getchar();
	getchar();
}
