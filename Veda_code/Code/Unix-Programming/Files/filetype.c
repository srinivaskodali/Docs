
/* To test the file type. 
Team : IDST
Version : 1.0
*/

#include	<sys/types.h>
#include	<sys/stat.h>
int main(int argc, char *argv[])
{
	int i;
	struct stat buf;
	char *ptr;
	if(argc !=2){
		printf("Usage: ftype filename\n");	
		exit(2);
	}
	printf("%s: ", argv[1]);
	if (lstat(argv[1], &buf) < 0) {
		perror("lstatfailed:");
		exit(1);
	}

		if(S_ISREG(buf.st_mode))
			ptr = "regular";
		else if(S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if(S_ISCHR(buf.st_mode)){
			ptr = "character special";
			printf("Major = %d \n",major(buf.st_rdev));
			printf("Minor = %d \n",minor(buf.st_rdev));
		}
		else if(S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if(S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if(S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else
			ptr = "** unknown mode **";
		printf("File Type :  %s\n", ptr);
		printf(" file owner = %d \n", buf.st_uid);
		printf(" file group = %d \n", buf.st_gid);
		printf(" file size = %d \n", buf.st_size);
		printf(" block size = %d \n", buf.st_blksize);
}
/* stat is same as lstat in case of lstat it gives statistics of link instead
 of file opinted by link. fstat is same as stat.
*/
