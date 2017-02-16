
/* Try to find whether we are using posix 1 or posix 2
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <unistd.h>
main(){
#ifdef __USE_POSIX
	printf(" we are no posix 1.0 \n");
#endif

#ifdef __USE_POSIX2
	printf(" we are no posix 2.0 \n");
#endif
}
