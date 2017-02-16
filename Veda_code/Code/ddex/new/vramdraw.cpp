//-------------------------------------------------------------------
//	vramdraw.cpp
//
//	This application exercises services of our 'vram.c' driver;
//	however, it has 'bug' that you need to diagnose and repair.
//
//
//-------------------------------------------------------------------

#include <stdio.h>	// for printf(), perror() 
#include <fcntl.h>	// for open() 
#include <stdlib.h>	// for exit() 
#include <unistd.h>	// for read(), write(), close() 

#define HMAX 1280
#define VMAX 1024
char devname[] = "/dev/vram";

int main( void )
{
	// install our driver module
//	system( "/sbin/insmod vram.ko" );

	// open the device-file 
	int	fd = open( devname, O_RDWR );
	if ( fd < 0 ) { perror( devname ); exit(1); }
	getchar();

	// rotate pixels' color-components throughout the screen
	// 	red-->blue, blue-->green, green-->red
	for (int y = 0; y < VMAX; y++)
		{
		int	scanline[ HMAX ];
		lseek( fd, y*HMAX*4, SEEK_SET );
		read( fd, scanline, sizeof( scanline ) );
		for (int x = 0; x < HMAX; x++)
			{
			int	color = scanline[x] & 0x00FFFFFF;
			color = (color >> 4)|(color << 8);

			scanline[x] = color & 0x00FFFFFF;
			}
		lseek( fd, y*HMAX*4, SEEK_SET );
		write( fd, scanline, sizeof( scanline ) );
		}	
	getchar();

	// close the device-file and remove the driver-module
	close( fd );
	system( "/sbin/rmmod vram" );
}
