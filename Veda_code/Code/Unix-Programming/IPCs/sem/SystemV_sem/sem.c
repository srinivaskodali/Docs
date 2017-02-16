#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define KEY             (key_t)261
#define DEATH(mess) { perror(mess); exit(errno); }

union semun
{
    int val;                    /* value for SETVAL */
    struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
    unsigned short int *array;  /* array for GETALL, SETALL */
    struct seminfo *__buf;      /* buffer for IPC_INFO */
};

void set_sem (int semid, int val)
{
    struct sembuf buffer;

    buffer.sem_num = 0;         /* first (and only) semaphore in the list */
    buffer.sem_op = val;        /* either wait (-1) or release (1) */
    buffer.sem_flg = SEM_UNDO;  /* let the system clean up after us */

    if ((semop (semid, &buffer, 1)) == -1)
        DEATH ("setop");
}

void create_it (void)
{
    int semid;
    union semun sem_union;

    printf ("Creating a new semaphore\n");
    if ((semid = semget (KEY, 1, 0666 | IPC_CREAT)) == -1)
        DEATH ("semget");

    printf ("Initializing the semaphore.\n");
    sem_union.val = 1;
    if ((semctl (semid, 0, SETVAL, sem_union)) == -1)
        DEATH ("semctl");

    printf ("Semaphore successfully created and initialized\n");
    exit (EXIT_SUCCESS);
}

void remove_it (void)
{
    int semid;
    union semun sem_union;

    if ((semid = semget (KEY, 1, 0)) == -1)
        DEATH ("semget");

    if ((semctl (semid, 0, IPC_RMID, sem_union)) == -1)
        DEATH ("semctl");

    printf ("Semaphore successfully deleted\n");
    exit (EXIT_SUCCESS);
}

void protect_it (void)
{
    int semid, i;

    if ((semid = semget (KEY, 1, 0)) == -1)
        DEATH ("semget");

    for (i = 0; i < 4; i++) {
        set_sem (semid, -1);
        printf ("Entering critical section, %d, pid=%d\n", i, getpid ());
        sleep (3);
        printf (" Leaving critical section, %d, pid=%d\n", i, getpid ());
        set_sem (semid, 1);
        sleep (3);
    }
    printf ("PROTECT region exited for pid=%d\n", getpid ());

    exit (EXIT_SUCCESS);
}

int main (int argc, char *argv[])
{
    if (argc > 1) {
        if (!strcasecmp ("create", argv[1]))
            create_it ();
        if (!strcasecmp ("remove", argv[1]))
            remove_it ();
        if (!strcasecmp ("protect", argv[1]))
            protect_it ();
    }
    printf ("Usage: %s  create | remove | protect\n", argv[0]);
    exit (-1);
}
