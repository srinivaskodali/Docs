/*
This program performs an experiment with our 'vma.c' module.
It displays the contents of the '/proc/vma' pseudo-file both
before and after allocating a large amount of heap-space. 

Author:Team Veda
Version:1.0
Tested with: Linux kernel version 2.6.29 also
*/

#include <stdio.h>	// for printf(), perror() 
#include <fcntl.h>	// for open() 
#include <stdlib.h>	// for exit(), malloc(), free()
#include <unistd.h>	// for read(), close() 

char filename[] = "/proc/vma";

int main( int argc, char **argv )
{
	int	fd, nbytes;
	char	info[ 4096 ] = {0};

	// open the pseudo-file for reading
	fd = open( filename, O_RDONLY );
	if ( fd < 0 )
	 {
		 perror( filename );
		 exit(1);
	 }

	// read and display the contents of the file
	nbytes = read( fd, info, sizeof( info ) );
	if ( nbytes < 0 ) 
	{ 
		perror( "read" );
	        exit(1); 
	}
	printf( "%s", info );
	getchar();

	// use 'malloc()' allocate space from the heap
	unsigned long	heapsize = (256 << 20);	// 256-megabytes
	void	*myheap = malloc( heapsize );
	if ( !myheap )
	 {
		 perror( "malloc" );
		 exit(1);
	 }

	printf( "allocated 0x%08lX bytes on the heap ", heapsize );
	printf( "at virtual address %08lX \n", (unsigned)myheap );	 
	getchar();

	// again read and display the contents of the file
	lseek( fd, 0, SEEK_SET );
	nbytes = read( fd, info, sizeof( info ) );
	if ( nbytes < 0 )
	 { perror( "read" ); 
	   exit(1); 
	 }
	printf( "%s", info );
	getchar();

	// release the heap space 
	free( myheap );	
	printf( "released heap space \n" );
}
