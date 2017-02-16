/* Very use to test whether a specific option is supported by system or not
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <limits.h>
# include <bits/posix_opt.h>

main(){
# ifdef _POSIX_JOB_CONTROL
	printf("Posix job control is supported\n");
#endif
#ifdef _POSIX_FSYNC
	printf(" fsync is present \n");
#endif
#ifdef _POSIX_CHOWN_RESTRICTED
	printf(" chown command has restrictions \n");
#endif
}
/* when we write portable code we need to check whether a feature is present
in a system or not at compile time and provide the code accordingly.

All the above are defined in bits/posix_opt.h.
*/	
