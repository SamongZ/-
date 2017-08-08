#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include "shm_com.h"

int main()
{
    int shmid;
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed.\n");
        exit(EXIT_FAILURE);
    }
    void *shared_memory = (void*)0;
    shared_memory = shmat(shmid, (void*)0, 0);
    if (shared_memory == (void*)-1) {
        fprintf(stderr, "shmat failed.\n");
        exit(EXIT_FAILURE);
    }
    struct shared_use_st *shared_stuff;
    shared_stuff = (struct shared_use_st*)shared_memory;
    shared_stuff -> written = 0;
    while (1) {
        if (shared_stuff -> written) {
            printf("receive data: %s", shared_stuff -> text);
            shared_stuff -> written = 0;
            if (strncmp(shared_stuff -> text, "end", 3) == 0)
                break;
        }
    }
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed.\n");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl failed.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
