

#include "ser1.h"

main(){
	int fd;
	struct termios *oldser,*newser,*oldter,*newter;
	oldser=(struct termios *)malloc(sizeof(struct termios));
	newser=(struct termios *)malloc(sizeof(struct termios));
	oldter=(struct termios *)malloc(sizeof(struct termios));
	newter=(struct termios *)malloc(sizeof(struct termios));
	fd=openSerial("/dev/ttyS1");
	setSerial(fd,oldser,newser);
	/* next stop echo and buffering for stdin */
 	tcgetattr(0,oldter);
 	tcgetattr(0,newter); /* get working stdtio */
 	newter->c_lflag &= ~(ICANON | ECHO);
 	tcsetattr(0,TCSANOW,newter);
	writeToSerial(fd,'x');
   	tcsetattr(fd,TCSANOW,oldser); /* restore old serial setings */
	close(fd);
   	tcsetattr(0,TCSANOW,oldter); /* restore old tty setings */
	exit(0);
}
