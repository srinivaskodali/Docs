	/* used to check for the existence of the file and whether we can 
open file for read , write ,execute or not. The checking is performed 
based on real uid.
*/

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf(" uid is %d\n",getuid());
	printf(" euid is %d\n",geteuid());
	if (access(argv[1], F_OK) < 0){
		printf(" file is not existing \n");
		exit(1);
	}
	printf(" File exists \n");
	if( access(argv[1],R_OK) <0) // we can use W_OK ,X_OK also
		printf(" file cannot be read \n");
	else
		printf(" File can be read \n");
	if(open(argv[1],O_RDONLY) >=0){
		printf(" file is opened \n");
	}
	
}
