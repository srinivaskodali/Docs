# include <stdio.h>
# include <fcntl.h>
#include <errno.h>

main(){
	open("/nonexistingfile",O_RDONLY);
	printf("%d \n",errno);
	perror("OURPRG:");
}
