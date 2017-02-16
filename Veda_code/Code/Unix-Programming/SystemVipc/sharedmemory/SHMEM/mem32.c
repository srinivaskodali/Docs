/* shows how to use shared memory
Version : 1.0
Author : Team -C
*/

# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/types.h>
# include "memkey.h"

main(){
	int shm_id,i;
	key_t key = IPC_KEY;
	void *sharedarea;
	int *intptr;
	shm_id = shmget(key,8000,IPC_CREAT);
	if(shm_id <0){
		perror("shmget:");
		exit(1);
	}
	printf("shm_id = %d\n",shm_id);
	sharedarea = shmat(shm_id,0,SHM_RDONLY);	
	if( sharedarea < 0){
		perror("shmat:");
		exit(1);
	}
	printf("shared are in this process starts from %x\n",sharedarea);
	intptr= (int *) sharedarea;
	for(i=0;i<10;i++){
		printf("%d\n",*intptr);
		intptr++;
		}
		
}
