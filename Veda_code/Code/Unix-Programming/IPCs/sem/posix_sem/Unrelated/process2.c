#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

struct region {        /* Defines "structure" of shared memory */
	int len;
	char buf[100];
};
#define MAX_LEN sizeof(struct region)*3
#define NAME "/my_sem"


sem_t *mysem;


void open_sem (void)
{

    /* Creating &  initializing semaphores object */
    if ((mysem = sem_open (NAME, 0)) == SEM_FAILED)
    {
        printf("\n Failed to open semaphores object\n");
        exit(1);
    }
    printf ("Semaphore successfully opened\n");
	getchar();
}



int main()
{
	void *shm_area;
	struct region *rptr;
	int fd;

	/* Create shared memory object and set its size */
	
	
	fd = shm_open("myshm", O_RDWR , 0);
	if (fd == -1)
	{
	    printf("\n Failed to open shared memory object\n");
	    exit(1);
	}


	if (ftruncate(fd,  MAX_LEN) == -1)
	    printf("\n Failed to set the size of the shared memory object\n");

	/* Map shared memory object */
	shm_area = mmap(NULL,  MAX_LEN,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (rptr == MAP_FAILED)
	    printf("\n Failed to map the shared memory\n");

	open_sem();
	if (sem_wait (mysem))
        {
            printf("\n Failed to Lock Semaphore\n");
            exit(1);
        }
		rptr = (struct region *)shm_area;
		printf("\n %d %s \n",rptr->len,rptr->buf);
		rptr++;
		printf("\n %d %s \n",rptr->len,rptr->buf);
		rptr++;
		printf("\n %d %s \n",rptr->len,rptr->buf);
		if (munmap (shm_area, MAX_LEN))
        	    printf("\n Failed to map the shared memory\n");
	sem_post (mysem);
	sem_unlink (NAME);	
	shm_unlink("myshm");
}
