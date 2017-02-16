
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#define BAUDRATE B38400

#define FALSE 0
#define TRUE 1

int openSerial(char *); //pass a device name like  /dev/ttyS1

int setSerial(int,struct termios *, struct termios *);
/*setSerial function arguments are file descriptor, and two termios structure variables
*/

void writeToSerial(int,char);
/*the arguments of writeToSerial are file descriptor and end character
*/
int readFromSerial(int);//pass file descriptor as an agument

int clearSerial(int);//pass file descriptor as an agument
   

