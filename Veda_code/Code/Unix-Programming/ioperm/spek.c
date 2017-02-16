/* This program shows how to  probe for a mouse
Author : Team - C
Version : 1.0
Remarks : we should run this program as root user
*/
# include <unistd.h>
# include <sys/io.h>

# define TIMER_FREQ 1193180
pause(){
	int i;
	for(i=0;i<9999;i++);
}
long_pause(){
	long i;
	float a=22.2,b=334.4,c=98.0;
	for(i=0;i<99999999;i++)
		a=b*c/a; /* just to kill time */
}
main(){
	/* get the permission to access rtc ports */
	int res,cons,i;
	res=ioperm(0x40,0x40,1);/* we can access ports now*/
	printf(" res of ioperm = %d\n",res);
	for(i=1;i<10;i++){
		cons = (TIMER_FREQ)/(i*22);  
		outb(inb(0x61)|3,0x61);
		outb(0xb6,0x43);
		outb(cons &0xff,0x42);
		outb((cons>>8) &0xff,0x42);
		long_pause();
		outb(inb(0x63)&0xfc,0x61);
	}

}

/* The speaker in the system is connected to latch at port no 0x61.
Timer can be used to generate input to speaker (square wave).
8253 timer has 3 timers, in these the Timer 2 is connected to the
speaker. In order to generate sound we need to make use of Timer 2.

Algorithm Used:
	Step 1: Set the speaker.
	Step 2: program the timer to generate square wave.
	Step 3: Off the Speaker.

Source : Books on PC Architecture and Linux Kernel Internals.


details of programming timer and setting/stopping the speaker.

1. bit no 0 and bit no 1 has to be set to 1 to start speaker
   at port no 0x61.

2. bit no 0 and bit no 1 has to be set to 0 to stop the speaker.

3. Port 0x43 is control register of timer.

4. port 0x40 is dataport of timer 0 , 0x41 is dataport of timer 1 and
   port no 0x42 is dataport of timer 2.

5. To generate a square wave of particular frequency we use the
    formula timerconstant/1193180. we need to write the constant to
   port no 0x42.
6. Here is the meaning of 8 bits that we have to put in port 0x43.
	7 , 6 -- indicates the timer to be programmed.
	5 , 4 -- access mode  11 for we set LSB follwed by MSB.
	3 , 1 -- timer mode. ( we use mode 3)

in our example we use the bits like
10      11         110          0  -- 0xb6.
timer2  LSB-MSB    Timer 2    unused
*/
