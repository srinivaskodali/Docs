/* shows how to use ftok to generate ipc key without hardcoding
ipc key in the header file
Version: 1.0
Author : Team -C
*/

# include <sys/types.h>
# include <sys/ipc.h>

main(){
	key_t key;
	key = ftok("/var/run/inetsolv",1);
	printf(" key = %d\n",key);
	key = ftok("/var/run/inetsolv",1);
	printf(" key = %d\n",key);
	key = ftok("/var/run/inetsolv",2);
	printf(" key = %d\n",key);
}
