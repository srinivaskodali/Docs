/*
This program performs an experiment with our 'vma.c' module.
It displays the contents of the '/proc/vma' pseudo-file both
before and after forking a child process. 

Author:Team Veda
Version: 1.0
*/

#include <stdio.h>	// for printf(), perror() 
#include <fcntl.h>	// for open() 
#include <stdlib.h>	// for exit() 
#include <unistd.h>	// for read(), close()
#include <sys/wait.h>	// for wait() 

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

	// flush the standard output device-file
	fflush( stdout );

	// use 'fork()' to create a child-process
	if ( fork() ) wait( NULL );

	// again read and display the contents of the file
	lseek( fd, 0, SEEK_SET );
	nbytes = read( fd, info, sizeof( info ) );
	if ( nbytes < 0 )
	 { 
		perror( "read" );
	        exit(1); 
	 }
	printf( "%s", info );
}
