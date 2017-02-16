/* This program shows how to access the io details from a user
space program ( not inside kernel )
Author : Team - C
Version : 1.0
Remarks : we should run this program as root user
*/
# include <unistd.h>
# include <sys/io.h>
//# include "const1.h"

unsigned char getval(int what){
	outb(what,0x70);
	return (inb(0x71));
}
main(){
	/* get the permission to access rtc ports */
	int res,a,b;
	res=ioperm(0x70,0x04,1);/* we can access ports 70,71,72,73*/
	printf("res =%d \n",res);
	printf(" year= %x \n",getval(9));
	printf(" month = %x \n",getval(8));
	printf(" day = %x \n",getval(7));
	printf(" hours = %x \n",getval(4));
	printf(" minutes = %x \n",getval(2));
	printf(" seconds = %x \n",getval(0));
}
