/* This program shows how to access the io details from a user
space program ( not inside kernel )
Author : Team - C
Version : 1.0
Remarks : we should run this program as root user
*/
# include <unistd.h>
# include <sys/io.h>
//# include "const1.h"

void setval(int what,unsigned val){
	outb(what,0x70);
	outb(val,0x71);
}
main(){
	/* get the permission to access rtc ports */
	int res,a,b;
	res=ioperm(0x70,0x04,1);/* we can access ports 70,71,72,73*/
	printf("res =%d \n",res);
	setval(9,0x05);
	printf(" year = %x \n",inb(0x71));
	setval(8,0x09);
	//outb(8,0x70);
	printf(" month = %x \n",inb(0x71));
}
