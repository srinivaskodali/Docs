/* shows some of the run time limts
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <limits.h>
# include <unistd.h>

/* we can get the macro definitions of _SC and _PC that need to be
used with sysconf and pathconf from bits/confname.h file , we need
not directly include it
*/

main(){
	printf(" Following are the minimum limits specified by posix\n");
	printf(" Max length of arguments to programs = %d\n",\
		sysconf(_SC_ARG_MAX));
	printf(" Max no of links to files %d\n",\
		pathconf("/",_PC_LINK_MAX));
	printf(" No of files that can be open by a process = %d\n",\
		sysconf(_SC_OPEN_MAX));
	printf(" No of bytes in file name = %d\n",\
		pathconf("/", _PC_NAME_MAX));
	printf(" No of bytes in path name = %d\n",\
		pathconf("/",_PC_PATH_MAX));

}
	
