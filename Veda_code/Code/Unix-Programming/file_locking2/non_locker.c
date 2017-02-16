/*

  Purpose: Demonstrate mandatory file-level locking via fcntl().  
  This is a companion program to non_locker.
  Team :IDST
  Version : 1.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>
#include "common.h"

/* -------------------------------------------------------------- 

  PLEASE NOTE: This sample will only work properly if the disk 
  volume that contains the test file has been mounted with the 
  mandatory locking option.  You can remount a volume and specify
  this option with the command:

    mount /dev/hda1 / -oremount -omand

  Where "/dev/hda1" and "/" should be changed to reflect your actual
  volume device name and the mount point, obviously.  "-oremount"
  tells mount to re-mount the volume, and "-omand" tells it to 
  enable mandatory locking.

  ---------------------------------------------------------------

  Important note: There are two mechanisms for file locking under
  Linux, flock() and fcntl().  See the file Documentation/locks.txt
  in your Linux source code (typically in the directory 
  /usr/src/linux) for the whole sordid story, but the most 
  important point is that the two methods, flock() and fcntl(),
  do not interoperate at all.  Also, this file details that 
  there are two types of file locking under Linux, advisory and
  mandatory.  The locks used in this sample are advisory, meaning
  there's nothing to stop a program from ignoring a failed attempt
  to acquire a lock and using the file anyway.  

  Mandatory locks, as described in Documentation/mandatory.txt, 
  are only enabled if the disk volume was mounted with a 
  specific option and the file has an odd and otherwise meaningless
  set of mode bits (group ID is on but group execute is off), and 
  can only be set via fcntl().  Mandatory locks actually prevent 
  one process from accessing a file in violation of another process' 
  lock.

  ---------------------------------------------------------------

  locker and non_locker compete for locks on a file, dummy_file.txt.
  Run locker first, then follow the prompts to walk through this 
  sequence of steps:

  locker will acquire a read lock

                                 non_locker will acquire a read lock
                        non_locker will fail to acquire a write lock

  locker will release its read lock
  locker will acquire a write lock

           non_locker will try to read from the file, making it hang

  locker will release its lock

            non_locker's read attempt will finally end, successfully

  --------------------------------------------------------------- */

#define buffer_size 86

 main(int argc, char **argv)
{
  int fd;
  char buffer[buffer_size];

  /* Open our file for read/write access.  Note that normally this
     file will already be open for r/w access by locker. */

  if((fd = open(file_name, O_RDWR)) < 0)
  {
    perror("open");
    exit(EXIT_FAILURE);
  }

  /* Acquire a read lock. */

  if(setLock(fd,F_RDLCK) == 0)
  {
    printf("Read lock has been acquired, as expected.\n\nHit ENTER... ");
    getchar();
  }
  else
  {
    printf("Unable to set read lock.  Program is terminating.\n");
    close(fd);
    exit(EXIT_FAILURE);
  }

  /* Release the shared lock. */

  if(setLock(fd,F_UNLCK) == 0)
    printf("Read lock has been released\n\n");
  else
  {
    printf("Unable to release read lock.  Program is terminating.\n");
    close(fd);
    exit(EXIT_FAILURE);
  }

  /* Try to acquire a write lock. */

  if(setLock(fd,F_WRLCK) == 0)
  {
    printf("Acquired a write lock--this shouldn't happen! Program is terminating.\n");
    setLock(fd,F_UNLCK);
    close(fd);
    exit(EXIT_FAILURE);
  }

  printf("Failed to acquire the write lock, as expected.\n\n");
  printf("Go hit ENTER in the locker terminal to let it switch to\n");
  printf("a write lock, then come back here and hit ENTER.\n");
  getchar();

  /* Try to acquire a read lock. */

  if(setLock(fd,F_RDLCK) == 0)
  {
    printf("Acquired a read lock--this shouldn't happen! Program is terminating.\n");
    setLock(fd,F_UNLCK);
    close(fd);
    exit(EXIT_FAILURE);
  }

  printf("Failed to acquire the write lock, as expected.\n\n");
  printf("Hit ENTER and we'll try to read the file.  This call should\n");
  printf("block and hang this program until locker releases its lock\n");
  printf("on the file.  Once this program hangs, go hit ENTER in the\n");
  printf("locker terminal.\n");
  getchar();

  printf("Attempting to read file... \n\n");
  if(read(fd,buffer,buffer_size) == buffer_size)
  {
    printf("Successfully read from the file.\n");
    buffer[buffer_size - 1] = '\0';
    printf("Data read: \"%s\"\n",buffer);
  }
  else
    printf("Could not read from the file.\n");

  close(fd);

  /* Indicate normal termination via the 
     EXIT_SUCCESS constant from stdlib.h */

  return EXIT_SUCCESS;
}
