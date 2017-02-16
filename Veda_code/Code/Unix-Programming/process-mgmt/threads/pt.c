
























































































/* shows how to create multiple threads of control , Earlier we didn this
using clone.
Version : 1.0
Author: Team -C.
*/

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>

void * startofthone(void *arg){
	int i=0;
}

main(){
	pthread_t pt1;
	pthread_create(&pt1,NULL,startofthone,NULL);	
}
