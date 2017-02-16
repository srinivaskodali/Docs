/*
 *        Application reads data for Read.txt file and write to Write.txt file using splice system call
 *        Author: Team Veda
 *        linux-2.6.25-i386
 *        version: 1.0
 *  
*/



#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>

#define LEN 100

int main()
{
	int fd_r,fd_w,mypipe[2];
	pid_t Cpid;
	int len, slen;

	/* Create a pipe */
	pipe(mypipe);
	
	/* Create child process */
	Cpid = fork();

	if(Cpid == 0)
	{
		/* Close read end of the pipe in child process */
		close(mypipe[0]);
		fd_r = open("read.txt", O_RDONLY);
		while(1)
        	{
			/* moves data from read.txt file into pipe */ 
                	len = splice(fd_r,NULL,mypipe[1],NULL,LEN,SPLICE_F_MOVE);
                	if(len==0)
                	        break;
		}
	}
	else
	{
		/* Close write end of the pipe in parent process */
		close(mypipe[1]);
		fd_w = open("write.txt",O_WRONLY | O_CREAT , 0644);
	
		while(1)
		{
			/* moves data from pipe into write.txt */ 
			len = splice(mypipe[0],NULL,fd_w,NULL,LEN,SPLICE_F_MOVE);
			printf(" %d \n",len);
			if(len==0)
				break;
		}
	}

}
