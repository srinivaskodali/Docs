/* This program shows how to access the io details from a user
space program ( not inside kernel )
Author : Team - C
Version : 1.0
Remarks : we should run this program as root user
*/
# include <unistd.h>
# include <sys/io.h>

main(){
	/* get the permission to access rtc ports */
	int res,a,b;
	res=ioperm(0x70,0x04,1);/* we can access ports 70,71,72,73*/
	printf("res =%d \n",res);
	/* to access ports we can use inb and outb functions */
/* to access year */
	outb(9,0x70);
	printf(" year= %x \n",inb(0x71));
/* to access month */
	outb(8,0x70);
	printf(" month = %x \n",inb(0x71));
/* to access day */
	outb(7,0x70);
	printf(" day = %x \n",inb(0x71));
}
