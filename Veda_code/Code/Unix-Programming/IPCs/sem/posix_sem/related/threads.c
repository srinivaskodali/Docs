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
struct region *rptr;
#define MAX_LEN sizeof(struct region)*3 
sem_t mysem;

void init_sem(void)
{
	if (sem_init(&mysem, 0, 1) == -1)
	{
		printf("\n Unable to init sem \n");
		exit(1);
	}
		
}

void * write_thread(void *arg)
{
	if (sem_wait (&mysem))
        {
            printf("\n Failed to Lock Semaphore\n");
            exit(1);
        }
	printf("\n In Write Thread\n Writing data into shared memory\n");
        strcpy(rptr->buf,"Message One");
        rptr->len=strlen("Message One");
        rptr++;
        strcpy(rptr->buf,"Message Two");
        rptr->len=strlen("Message Two");
        rptr++;
	sleep(1);
        strcpy(rptr->buf,"Message Three");
        rptr->len=strlen("Message Three");		
	rptr-=2;
	sem_post (&mysem);
	printf("\n End of write thread \n");
}

void * read_thread(void *arg)
{
        printf("\nIn Child \n Reading data from shared memory\n");
	if (sem_wait (&mysem))
        {
            printf("\n Failed to Lock Semaphore\n");
            exit(1);
        }
        printf("\n %d %s \n",rptr->len,rptr->buf);
        rptr++;
        printf("\n %d %s \n",rptr->len,rptr->buf);
        rptr++;
        printf("\n %d %s \n",rptr->len,rptr->buf);
	rptr-=2;
	sem_post (&mysem);
	printf("\n End of read thread \n");
}

int main()
{
	pthread_t tid1,tid2;

	void *shm_area;	
	int fd;

	/* Create shared memory object and set its size */
	
	
	fd = shm_open("./myshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
	    printf("\n Failed to open shared memory object\n");


	if (ftruncate(fd, sizeof(struct region)) == -1)
	    printf("\n Failed to set the size of the shared memory object\n");

	/* Map shared memory object */
	shm_area = mmap(NULL, sizeof(struct region),PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (rptr == MAP_FAILED)
	    printf("\n Failed to map the shared memory\n");
	
	init_sem();

	rptr = (struct region *)shm_area;
	pthread_create(&tid1,NULL,write_thread,NULL);
	pthread_create(&tid2,NULL,read_thread,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

        if (munmap (shm_area, MAX_LEN))
       	    printf("\n Failed to map the shared memory\n");
	close(fd);
	shm_unlink("myshm");
	sem_destroy(&mysem);
}
