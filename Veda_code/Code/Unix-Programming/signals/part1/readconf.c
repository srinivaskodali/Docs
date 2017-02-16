/* shows how to change the behaviour after re-reading conf file
Version : !.0
Author : Team -C
*/

# include <signal.h>
# include <stdio.h>


FILE *fp=NULL;
char u_name[100];

void sighand(int signum){
	fp = fopen("./prog.conf","r");
	fscanf(fp,"%s",u_name);
	fclose(fp);
}

main(){
	signal(1,sighand);
	fp = fopen("./prog.conf","r");
	fscanf(fp,"%s",u_name);
	fclose(fp);
	while(1){
		printf("I am working for Mr. %s\n",u_name);
	}
}
