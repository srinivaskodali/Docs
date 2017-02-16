//-------------------------------------------------------------------
//	vrammdraw.cpp     (Improved version of 'vramdraw.cpp' demo) 
//
//	This program invokes the 'mmap()' function of our 'vramm.c' 
//	device-driver in order to benefit from direct access to the
//	system's video display memory from user-space .
//
//
//-------------------------------------------------------------------

#include <stdio.h>	// for printf(), perror() 
#include <fcntl.h>	// for open() 
#include <stdlib.h>	// for exit() 
#include <unistd.h>	// for close() 
#include <sys/mman.h>	// for mmap(), munmap()

#define HMAX 1280		// horiz resolution of display screen
#define VMAX 1024		// vertl resolution of display screen
char devname[] = "/dev/vram";	// <--- keeps former device-file name

int main( void )
{
	// install our driver module
//	system( "/sbin/insmod vramm.ko" );

	// open the device-file 
	int	fd = open( devname, O_RDWR );
	if ( fd < 0 ) { perror( devname ); exit(1); }
	getchar();
	// map the video display memory to user-space
	int	size = HMAX * VMAX * 4;
	int	prot = PROT_READ | PROT_WRITE;
	int	flag = MAP_FIXED | MAP_SHARED;
	void	*vm = (void*)0xA0000000;
	if ( mmap( vm, size, prot, flag, fd, 0 ) == MAP_FAILED )
		{ perror( "mmap" ); exit(1); }
	getchar();
	// rotate pixels' color-components throughout the screen
	// 	red-->blue, blue-->green, green-->red
	unsigned long	*vram = (unsigned long*)vm;
	for (int y = 0; y < VMAX; y++)
		for (int x = 0; x < HMAX; x++)
			{
			int	where = y * HMAX + x;
			int	color = vram[ where ] & 0x00FFFFFF;
			color = (color >> 8)|(color << 16);
			vram[ where ] = color & 0x00FFFFFF;
			}

	// close and unmap the device-file, then remove the driver-module
	close( fd );
	munmap( vm, size );
//	system( "/sbin/rmmod vramm" );
}
