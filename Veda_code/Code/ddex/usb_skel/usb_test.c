#include <fcntl.h>
main()
{
	int fd;
	char buf[10];
	fd = open("/dev/USBSkel",O_RDONLY);
	read(fd,buf,10);
	printf("\n buf = %s",buf);
}
