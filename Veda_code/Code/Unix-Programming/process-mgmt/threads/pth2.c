/* shows how to create multiple threads of control , Earlier we didn this
using clone.
Version : 1.0
Author: Team -C.
*/

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>

void * startofthone(void *arg){
	while(1)
		printf(" TOC 1\n");
}

void * startofthtwo(void *arg){
	while(1)
		printf("** TOC 2\n");
}

main(){
	pthread_t pt1,pt2;
	pthread_create(&pt1,NULL,startofthone,NULL);	
	pthread_create(&pt2,NULL,startofthtwo,NULL);	
	getchar();
	printf("end of main thread \n");
}
