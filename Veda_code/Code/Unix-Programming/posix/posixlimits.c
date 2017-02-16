/* shows some of the limts that are defined according to ANSI C
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <limits.h>

/* we need not include posix_lim.h> files as it will be automatically
include by limits.h
*/

main(){
	printf(" Following are the minimum limits specified by posix\n");
	printf(" Minimum length of arguments to programs = %d\n",\
				_POSIX_ARG_MAX);
	printf(" Minimum no of links to files %d\n",_POSIX_LINK_MAX);
	printf(" No of files that can be open by a process = %d\n",\
				_POSIX_OPEN_MAX);
	printf(" No of bytes in file name = %d\n", _POSIX_NAME_MAX);
	printf(" No of bytes in path name = %d\n", _POSIX_PATH_MAX);

}
	
