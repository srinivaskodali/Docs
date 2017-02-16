#include "ser1.h"

/* 
	Below function allows us to open a devices (ports) like ttyS1,ttyS2,....
	or any device file.
*/

int openSerial(char *port){
		int fd;
		printf(" Trying to open %s\n",port);
 		fd = open(port, O_RDWR | O_NOCTTY);
		if (fd <0) {
				perror(port);
				exit(-1);
		 }
		printf(" Port opened fd = %d\n",fd);
		return(fd);
}

int setSerial(int fd,struct termios *oldtio, struct termios *newtio){

	tcgetattr(fd,oldtio); // save current settings
 
 	/* 
 	 Set bps rate and hardware flow control and 8n1 (8bit,no parity,1 
	 stopbit).  Also don't hangup automatically and ignore modem status.		 Finally enable receiving characters.
	*/
 	newtio->c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

 	/*
	BAUDRATE is defined in the header file. That is typedef statement.This          value is set speed of flow  control.
	Flags:
	  	CRTSCTS is used to set control flow. 
		CS8 is size of a character of 8 bits.
		CLOCAL specfies that to ignore modem lines.
		CREAD is to enable  receiver.	
	*/
	/*
 	Ignore bytes with parity errors and make terminal raw and dumb.
	*/
	 newtio->c_iflag = IGNPAR;
 
	/*
 	Raw output.
	*/
 	newtio->c_oflag = 0;
 
	/*
	 Don't echo characters because if you connect to a host it or your
 	 modem will echo characters for you. Don't generate signals.
	*/
 	newtio->c_lflag = 0;
 
	/* blocking read until 1 char arrives */
	 newtio->c_cc[VMIN]=1;
	 newtio->c_cc[VTIME]=0;
 
	/* now clean the modem line and activate the settings for modem */
	 tcflush(fd, TCIFLUSH);
 	 tcsetattr(fd,TCSANOW,newtio);

	/*
  	Strange, but if you uncomment this command miniterm will not work
  	even if you stop canonical mode for stdout. This is a linux bug.
	*/
 	tcsetattr(1,TCSANOW,newtio); // stdout settings like modem settings 
	printf(" serial port setting modified\n");
	return(fd);
}

/*
 In this function we read data  from standard input and write the data 
 to the serial port.
*/

void writeToSerial(int fd,char end){
	int n;
	char c;
	do{
		c = getchar();
		printf(" char read = %c\n",c);
	 	n = write(fd,&c,1);
		if( n == -1)
			perror("serial:");
	}while(c != end);
}

int readFromSerial(int fd){
	int c;
    	read(fd,&c,1); /* serial dev */
    	write(1,&c,1); /* stdout */
	return c;
}


/*
 Close the serial port
*/
void closeSerial(int fd){
	close(fd);
}

/*
   Clear all the stuff currently in the serial input buffer
*/

void serialClear(fd)
int fd;
{
   int i = 0;
   char c[8],buffer[1024];

   buffer[0] = '\0';
   while (read(fd,c,1) > 0 && i < 1000) {
      if (c[0] == 0)
         c[0] = ' ';
      buffer[i++] = c[0];
      buffer[i] = '\0';
   }
}
