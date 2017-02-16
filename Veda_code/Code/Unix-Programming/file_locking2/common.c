/* 
/* A simple utility function to do our file locking via fcntl()
Team : IDST
Version :1.0
*/
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* A simple utility function to do our file locking via
   fcntl() and report the PID of the locking program, if 
   there is one.

   This function returns:
     0 if the lock was acquired
     1 if the lock was not acquired */

int setLock(int fd, int type)
{
  int return_code = 0;
  struct flock lock;

  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 1;

  lock.l_type = type;

  if((fcntl(fd,F_SETLK,&lock)) != 0)
  {
    return_code = 1;

    fcntl(fd,F_GETLK,&lock);
    if(lock.l_type != F_UNLCK)
    {
      switch(lock.l_type)
      {
        case(F_RDLCK):
          printf("A read lock is already set on that file by the program with PID %d.\n\n",lock.l_pid);
          break;

        case(F_WRLCK):
          printf("A write lock is already set on that file by the program with PID %d.s\n\n",lock.l_pid);
          break;
      }
    }
  }

  return return_code;
}
