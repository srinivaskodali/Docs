/*
 * Shared Memory
@*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

#define KEY (key_t)26

#define SIZE 8196

void create_it (void)
{
    int shmid;
    void *shm_area;

    if ((shmid = shmget (KEY, SIZE, IPC_CREAT | 0666)) == -1)
        DEATH ("shmget");

    if ((shm_area = shmat (shmid, (void *)0, 0)) == (void *)-1)
        DEATH ("shmat");

    printf ("CREATE: Memory attached at %lX\n", (unsigned long)shm_area);

    if (shmdt (shm_area) == -1)
        DEATH ("shmdt");

    printf ("Shared Memory Region successfully created\n");

    exit (EXIT_SUCCESS);
}

void remove_it (void)
{
    int shmid;

    if ((shmid = shmget (KEY, SIZE, 0)) == -1)
        DEATH ("shmget");

    if (shmctl (shmid, IPC_RMID, 0))
        DEATH ("shmctl");

    printf ("Marked shared memory segment for deletion\n");

    exit (EXIT_SUCCESS);
}

void send_it (void)
{
    int shmid, iflag = 1;
    void *shm_area;

    if ((shmid = shmget (KEY, SIZE, 0)) == -1)
        DEATH ("shmget");

    if ((shm_area = shmat (shmid, (void *)0, 0)) == (void *)-1)
        DEATH ("shmat");

    printf ("SEND: Memory attached at %lX\n", (unsigned long)shm_area);
    memcpy (shm_area, &iflag, 4);

    if (shmdt (shm_area) == -1)
        DEATH ("shmdt");

    printf ("SENDND has successfully completed\n");

    exit (EXIT_SUCCESS);
}

void receive_it (void)
{
    int shmid, iflag = 8;
    void *shm_area;

    if ((shmid = shmget (KEY, SIZE, 0)) == -1)
        DEATH ("shmget");

    if ((shm_area = shmat (shmid, (void *)0, 0)) == (void *)-1)
        DEATH ("shmat");

    printf ("RCV: Memory attached at %lX\n", (unsigned long)shm_area);

    printf ("iflag is now = %d\n", iflag);
    memcpy (&iflag, shm_area, 4);
    
    printf ("RCV has successfully completed\n");
    printf ("iflag is now = %d\n", iflag);

    if (shmdt (shm_area) == -1)
        DEATH ("shmdt");

    exit (EXIT_SUCCESS);
}

int main (int argc, char *argv[])
{
    if (argc > 1) {
        if (!strcasecmp ("create", argv[1]))
            create_it ();
        if (!strcasecmp ("remove", argv[1]))
            remove_it ();
        if (!strcasecmp ("receive", argv[1]))
            receive_it ();
        if (!strcasecmp ("send", argv[1]))
            send_it ();
    }
    printf ("Usage: %s  create | remove | receive | send \n", argv[0]);
    exit (-1);
}
