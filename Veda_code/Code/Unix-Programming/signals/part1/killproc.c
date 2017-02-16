
/* shows how to send a signal to a process
Version: 1.0
Author : Team -C
*/


# include <sys/types.h>
# include <signal.h>
# include <stdio.h>

main(){
	pid_t pid;
	int sig_no;
	printf(" enter the pid of the process for which the signal\
need to be sent:");
	scanf("%d",&pid);
	printf("Enter the signal that need to be sent:");
	scanf("%d",&sig_no);
	kill(pid,sig_no);
	perror("Sig_res:");
}
	
