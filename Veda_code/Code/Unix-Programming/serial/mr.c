

#include "seriallib.h"

	main(){
		int fd,i;
		struct termios *ter1,*ter2,*ter3,*ter4;
		ter1=(struct termios *)malloc(sizeof(struct termios));
		ter2=(struct termios *)malloc(sizeof(struct termios));
		ter3=(struct termios *)malloc(sizeof(struct termios));
		ter4=(struct termios *)malloc(sizeof(struct termios));
		fd=openSerial("/dev/ttyS1");
		setSerial(fd,ter1,ter2);
		/* next stop echo and buffering for stdin */
 		tcgetattr(0,ter3);
 		tcgetattr(0,ter4); /* get working stdtio */
 		ter4->c_lflag &= ~(ICANON | ECHO);
 		tcsetattr(0,TCSANOW,ter4);

		i=readFromSerial(fd);
   		tcsetattr(fd,TCSANOW,ter1); /* restore old serial setings */
		close(fd);
   		tcsetattr(0,TCSANOW,ter3); /* restore old tty setings */
		close(0);
		printf("\n after resetting terminals\n");
		exit(0);
		
	}
